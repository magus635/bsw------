[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Spi.m
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

/****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
 *   V1.0.0:  19-Jul-2023  : Initial Version
 *
 ****************************************************************************************************/

[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!/* avoid multiple inclusion */!]
[!IF "not(var:defined('SPI_CFG_COMMON_M'))"!]
[!VAR "SPI_CFG_COMMON_M"="'true'"!]
[!AUTOSPACING!]
[!/**************************************************************************************************
**                                          Generate Macro                                         **
*****************************************************************************************************/!][!//
[!/*****************************************************************************
  MACRO: CG_GenerateCustomizeCsEnMacro
  Generate the macro definition whether enable Customer CS
*****************************************************************************/!]
[!MACRO "CG_GenerateCustomizeCsEnMacro"!][!//
[!//
[!INDENT "0"!][!//
[!VAR "CsCustomizeFlg" = "'false'"!][!//
[!LOOP "node:order(SpiDriver/SpiExternalDevice/*, './SpiExternalDeviceId')"!][!//
    [!IF "$CsCustomizeFlg = 'false'"!][!//
        [!IF "node:value(SpiEnableCs) = 'true' and node:exists(SpiCsSelection) = 'true'"!][!//
            [!IF "node:value(SpiCsSelection) = 'CS_VIA_GPIO'"!][!//
                [!VAR "CsCustomizeFlg" = "'true'"!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "$CsCustomizeFlg = 'true'"!][!//
    [!SELECT "as:modconf('Dio')[1]"!][!//
        [!IF "DioGeneral/DioFlipChannelApi = 'false'"!][!//
            [!ERROR!][!//
                [083-00-35-ERROR]: When using a custom chip select via GPIO, the macro switch "DioFlipChannelApi" is not enabled in the DIO module.!][!//
            [!ENDERROR!][!//
        [!ENDIF!][!//
    [!ENDSELECT!][!//
[!ENDIF!][!//
[!IF "$CsCustomizeFlg = 'false'"!][!//
    #define SPI_CUSTOMIZED_CS_EN                     (STD_OFF)
[!ELSE!][!//
    #define SPI_CUSTOMIZED_CS_EN                     (STD_ON)
[!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************
  MACRO: CG_GenerateSeqIdMacro
  Generate the macro definition for Sequence name
*****************************************************************************/!]
[!MACRO "CG_GenerateSeqIdMacro"!][!//
[!//
[!INDENT "0"!][!//
[!LOOP "node:order(SpiDriver/SpiSequence/*, './SpiSequenceId')"!][!//
    [!CALL "CG_FindSpiSequenceMappedCoreId", "SpiSequenceName"="node:name(.)"!][!//
    /* SpiSequenceId: [!"./SpiSequenceId"!] -> [!"node:name(.)"!], mapped to Core[!"$SpiSequenceMappedCoreId"!] */
    #ifndef SpiConf_[!"node:name(..)"!]_[!"node:name(.)"!]
    #define SpiConf_[!"node:name(..)"!]_[!"node:name(.)"!]        ((Spi_SequenceType)[!"./SpiSequenceId"!]U)
    #endif
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************
  MACRO: CG_GenerateJobIdMacro
  Generate the macro definition for Job name
*****************************************************************************/!]
[!MACRO "CG_GenerateJobIdMacro"!][!//
[!//
[!INDENT "0"!][!//
    [!LOOP "node:order(SpiDriver/SpiJob/*, './SpiJobId')"!][!//
        [!CALL "CG_FindSpiJobMappedCoreId", "SpiJobName" = "node:name(.)"!][!//
        /* SpiJobId: [!"./SpiJobId"!] -> [!"node:name(.)"!], mapped to Core[!"$SpiJobMappedCoreId"!] */
        #ifndef SpiConf_[!"node:name(..)"!]_[!"node:name(.)"!]
        #define SpiConf_[!"node:name(..)"!]_[!"node:name(.)"!]                  ((Spi_JobType)[!"./SpiJobId"!]U)
        #endif
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************
  MACRO: CG_GenerateChannelIdMacro
  Generate the macro definition for Channel name
*****************************************************************************/!]
[!MACRO "CG_GenerateChannelIdMacro"!][!//
[!//
[!INDENT "0"!][!//
    [!LOOP "node:order(SpiDriver/SpiChannel/*, './SpiChannelId')"!][!//
        [!CALL "CG_FindSpiChannelMappedCoreId", "SpiChannelName" = "node:name(.)"!][!//
        /* SpiChannelId: [!"./SpiChannelId"!] -> [!"node:name(.)"!], mapped to Core[!"$SpiChannelMappedCoreId"!] */
        #ifndef SpiConf_[!"node:name(..)"!]_[!"node:name(.)"!]
        #define SpiConf_[!"node:name(..)"!]_[!"node:name(.)"!]          ((Spi_ChannelType)[!"./SpiChannelId"!]U)
        #endif
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GenerateHwUnitIdMacro
  Generate the macro definition for Channel name
*****************************************************************************/!]
[!MACRO "CG_GenerateHwUnitIdMacro"!][!//
[!//
[!INDENT "0"!][!//
    [!LOOP "node:order(SpiDriver/SpiHwUnitConfig/*, './SpiHWUnitMapping')"!][!//
        [!CALL "CG_FindSpiHwUnitMappedCoreId", "SpiHwUnitName" = "node:name(.)"!][!//
        [!VAR "SpiHwUnitID" = "substring-after(node:value(./SpiHWUnitMapping),'Spi_')"!][!//
        /* SpiHwUnitId: [!"./SpiHwUnitId"!] -> [!"node:name(.)"!], mapped to ESPI[!"$SpiHwUnitID"!] in Core[!"$SpiHwUnitMappedCoreId"!] */
        #ifndef SpiConf_[!"node:name(..)"!]_[!"node:name(.)"!]
        #define SpiConf_[!"node:name(..)"!]_[!"node:name(.)"!]        ((Spi_ChannelType)[!"$SpiHwUnitID"!]U)
        #endif
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GenerateHwUnitMacro
  Get the HwUnit number(SPI hardware microcontroller peripherals (units/busses) )
*****************************************************************************/!]
[!MACRO "CG_GenerateHwUnitMacro"!][!//
[!//
[!INDENT "0"!][!//
    [!VAR "SpiHwUnitTotalNum" = "0"!][!//
    [!LOOP "node:order(SpiDriver/SpiHwUnitConfig/*, './SpiHWUnitMapping')"!][!//
        [!VAR "SpiHwUnitID" = "substring-after(node:value(./SpiHWUnitMapping),'Spi_')"!][!//
        [!CALL "CG_FindSpiHwUnitMappedCoreId", "SpiHwUnitName" = "node:name(.)"!][!//
        /* SpiHwUnitId: [!"./SpiHwUnitId"!] -> [!"node:name(.)"!], mapped to ESPI[!"$SpiHwUnitID"!] in Core[!"$SpiHwUnitMappedCoreId"!] */
        #ifndef SpiConf_[!"node:name(..)"!]_Espi[!"$SpiHwUnitID"!]
        #define SpiConf_[!"node:name(..)"!]_Espi[!"$SpiHwUnitID"!]            ((Spi_HWUnitType)[!"num:i($SpiHwUnitID)"!]U)
        #endif
        [!VAR "SpiHwUnitTotalNum" = "$SpiHwUnitTotalNum + 1"!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//

[!/**************************************************************************************************
**            Find HwUnit, ExDeviceHwUnit, ExDevice, Channel, Job, Sequence Corex ID               **
*****************************************************************************************************/!][!//
[!/*****************************************************************************
  MACRO: CG_FindSpiHwUnitMappedCoreId
  Find the core which the Spi HW unit is mapped to
*****************************************************************************/!]
[!MACRO "CG_FindSpiHwUnitMappedCoreId", "SpiHwUnitName" = ""!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "SpiHwUnitMappedCoreId" = "num:i(255)"!][!//
    [!VAR "SpiHwUnitMappedFlag" = "'false'"!][!//
    [!SELECT "as:modconf('Resource')[1]"!][!//
    [!LOOP "ResourceCoreConfigSet/ResourceCoreConfig/*"!][!//
        [!IF "./ResourceCoreEnable = 'true'"!][!//
            [!VAR "Resource_CoreId" = "./ResourceCoreId"!][!//
            [!LOOP "ResourceAllocation/*"!][!//
                [!IF "./ResourceModule = 'SPI'"!][!//
                    [!IF "node:refvalid(./ResourceModuleRef) = 'true'"!][!//
                        [!IF "$SpiHwUnitName = text:split(./ResourceModuleRef, '/')[last()]"!][!//
                            [!VAR "SpiHwUnitMappedCoreId" = "num:i(text:split($Resource_CoreId, 'CORE')[1])"!][!//
                            [!VAR "SpiHwUnitMappedFlag" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!ERROR!][!//
                            [083-00-21-ERROR]: Invalid resource allocation done in [!"$Resource_CoreId"!] for SPI module:[!"node:path(.)"!][!//
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//

    [!IF "$SpiHwUnitMappedFlag = 'false'"!][!//
        [!/* If not allocated the Spi HwUnit to any core then will default allocate it to core0 */!][!//
        [!VAR "SpiHwUnitMappedCoreId" = "num:i(0)"!][!//
    [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************
  MACRO: CG_FindSpiExternalDeviceMappedCoreId
   Find the core which the Spi external device is mapped to
*****************************************************************************/!]
[!MACRO "CG_FindSpiExternalDeviceMappedCoreId", "SpiExternalDeviceName" = ""!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "SpiExternalDeviceMappedCoreId" = "num:i(255)"!][!//
    [!SELECT "as:modconf('Spi')[1]"!][!//
        [!LOOP "node:order(SpiDriver/SpiExternalDevice/*, './SpiExternalDeviceId')"!][!//
            [!IF "$SpiExternalDeviceName = node:name(.)"!][!//
                [!CALL "CG_FindSpiHwUnitMappedCoreId", "SpiHwUnitName"="node:name(node:ref(./SpiHwUnitRef))"!][!//
                [!VAR "SpiExternalDeviceMappedCoreId" = "$SpiHwUnitMappedCoreId"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDSELECT!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************
  MACRO: CG_FindSpiJobMappedCoreId
  Find the core which the Spi Job is mapped to
*****************************************************************************/!]
[!MACRO "CG_FindSpiJobMappedCoreId", "SpiJobName" = ""!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "SpiJobMappedCoreId" = "num:i(255)"!][!//
    [!SELECT "as:modconf('Spi')[1]"!][!//
        [!LOOP "node:order(SpiDriver/SpiJob/*, './SpiJobId')"!][!//
            [!IF "node:name(.) = $SpiJobName"!][!//
                [!IF "node:refvalid(./SpiDeviceAssignment) = 'true'"!][!//
                    [!SELECT "node:ref(./SpiDeviceAssignment)"!][!//
                        [!/* Get HW unit number */!][!//
                        [!VAR "HwUnitName" = "node:name(node:ref(./SpiHwUnitRef))"!][!//
                        [!/* Get the core id that specified HW unit mapped to */!][!//
                        [!CALL "CG_FindSpiHwUnitMappedCoreId", "SpiHwUnitName"="$HwUnitName"!][!//
                        [!/* Core Id that current job mapped to */!][!//
                        [!VAR "SpiJobMappedCoreId" = "$SpiHwUnitMappedCoreId"!][!//
                    [!ENDSELECT!][!//
                [!ELSE!][!//
                    [!ERROR!][!//
                        [083-00-22-ERROR]: [!"node:name(.)"!]/SpiDeviceAssignment not reference a valid external device.
                    [!ENDERROR!][!//
                [!ENDIF!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDSELECT!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************
  MACRO: CG_FindSpiChannelMappedCoreId
  Find the core which the Spi Channel is mapped to
*****************************************************************************/!]
[!MACRO "CG_FindSpiChannelMappedCoreId", "SpiChannelName" = ""!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "ChannelUsedByJob" = "'false'"!][!//
    [!VAR "SpiChannelMappedCoreId" = "num:i(255)"!][!//
    [!SELECT "as:modconf('Spi')[1]"!][!//
        [!LOOP "node:order(SpiDriver/SpiJob/*/SpiChannelList/*, './SpiChannelIndex')"!][!//
            [!IF "$SpiChannelName = text:split(./SpiChannelAssignment, '/')[last()]"!][!//
                [!CALL "CG_FindSpiJobMappedCoreId", "SpiJobName" = "node:name(../../.)"!][!//
                [!VAR "SpiChannelMappedCoreId" = "$SpiJobMappedCoreId"!][!//
                [!/* A channel can only belong to a unique core, so only find out which core the job
                     that this channel assigned to just know which core this channel belong to */!][!//
                [!VAR "ChannelUsedByJob" = "'true'"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//

        [!IF "$ChannelUsedByJob = 'false'"!][!//
            [!ERROR!][!//
                [083-00-31-ERROR]: [!"$SpiChannelName"!] not reference a valid SpiJob.
            [!ENDERROR!][!//
        [!ENDIF!][!//
    [!ENDSELECT!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************
  MACRO: CG_FindSpiSequenceMappedCoreId
  Find the core which the Spi Sequence is mapped to
*****************************************************************************/!]
[!MACRO "CG_FindSpiSequenceMappedCoreId", "SpiSequenceName" = ""!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "SpiSequenceMappedCoreId" = "num:i(255)"!][!//
    [!SELECT "as:modconf('Spi')[1]"!][!//
        [!LOOP "node:order(SpiDriver/SpiSequence/*, './SpiSequenceId')"!][!//
            [!IF "$SpiSequenceName = node:name(.)"!][!//
                [!/* A sequence can only belong to a unique core, so all jobs assigned to this sequence
                     can only belong to a unique core. So just find out which core a job of all belong to,
                     indicate that core this sequence belong to */!][!//
                [!LOOP "SpiJobAssignment/*"!][!//
                    [!/* Find the core which assigned job mapped to */!][!//
                    [!VAR "CurrentJobName" = "text:split(., '/')[last()]"!][!//
                    [!/* Find the core which current job mapped to */!][!//
                    [!CALL "CG_FindSpiJobMappedCoreId", "SpiJobName" = "$CurrentJobName"!][!//
                    [!/* If core mismatch between jobs and sequence */!][!//
                    [!IF "$SpiSequenceMappedCoreId != num:i(255) and $SpiSequenceMappedCoreId != $SpiJobMappedCoreId"!][!//
                        [!ERROR!][!//
                            [083-00-23-ERROR]: The Job [!"$CurrentJobName"!] assigned to [!"$SequenceName"!] is mapped in core[!"$SpiJobMappedCoreId"!], but [!"$SequenceName"!] is mapped in Core[!"$SpiSequenceMappedCoreId"!]. All jobs allocated to the same sequence must belong to one core.
                        [!ENDERROR!][!//
                        [!BREAK!][!//
                    [!ELSE!][!//
                        [!VAR "SpiSequenceMappedCoreId" = "$SpiJobMappedCoreId"!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!/* The core of the current sequence has been found, exit the search */!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDSELECT!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/**************************************************************************************************
**                    Sequence, Job, Channel, HwUnit mapping configuration check                   **
*****************************************************************************************************/!][!//
[!/*****************************************************************************
  MACRO: CG_SpiAssignedConfigErrorDetect
  Configuration Error Check
*****************************************************************************/!]
[!MACRO "CG_SpiAssignedConfigErrorDetect"!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
[!/***      Check if the configured "SpiHwUnitConfig" is bound to a valid "SpiExternalDevice"      ***/!][!//
    [!LOOP "node:order(SpiDriver/SpiHwUnitConfig/*, './SpiHwUnitId')"!][!//
        [!VAR "UsedFlag" = "'false'"!][!//
        [!VAR "CurrentNodeName" = "node:name(.)"!][!//
        [!LOOP "node:order(../../SpiExternalDevice/*, './SpiExternalDeviceId')"!][!//
            [!IF "text:split(./SpiHwUnitRef, '/')[last()] = $CurrentNodeName"!][!//
                [!VAR "UsedFlag" = "'true'"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$UsedFlag = 'false'"!][!//
            [!WARNING!][!//
                [083-00-32-WARNING]: [!"$CurrentNodeName"!] not reference a valid SpiExternalDevice.
            [!ENDWARNING!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!/***      Check if the configured "SpiExternalDevice" is bound to a valid "SpiJob"      ***/!][!//
    [!LOOP "node:order(SpiDriver/SpiExternalDevice/*, './SpiExternalDeviceId')"!][!//
        [!VAR "UsedFlag" = "'false'"!][!//
        [!VAR "CurrentNodeName" = "node:name(.)"!][!//
        [!LOOP "node:order(../../SpiJob/*, './SpiJobId')"!][!//
            [!IF "text:split(./SpiDeviceAssignment, '/')[last()] = $CurrentNodeName"!][!//
                [!VAR "UsedFlag" = "'true'"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$UsedFlag = 'false'"!][!//
            [!ERROR!][!//
                [083-00-33-ERROR]: [!"$CurrentNodeName"!] not reference a valid SpiJob.
            [!ENDERROR!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!/***      Check if the configured "SpiJob" is bound to a valid "SpiSequence"      ***/!][!//
    [!LOOP "node:order(SpiDriver/SpiJob/*, './SpiJobId')"!][!//
        [!"node:path(.)"!]
        [!VAR "UsedFlag" = "'false'"!][!//
        [!VAR "CurrentNodeName" = "node:name(.)"!][!//
        [!LOOP "node:order(../../SpiSequence/*, './SpiSequenceId')"!][!//
            [!LOOP "./SpiJobAssignment/*"!][!//
                [!IF "text:split(., '/')[last()] = $CurrentNodeName"!][!//
                    [!VAR "UsedFlag" = "'true'"!][!//
                    [!BREAK!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDLOOP!][!//
        [!IF "$UsedFlag = 'false'"!][!//
            [!ERROR!][!//
                [083-00-34-ERROR]: [!"$CurrentNodeName"!] not reference a valid SpiSequence.
            [!ENDERROR!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!/***      Check whether all jobs assigned to same sequence belong to the same core      ***/!][!//
    [!VAR "SpiSequenceMappedCoreId" = "num:i(255)"!][!//
    [!LOOP "node:order(SpiDriver/SpiSequence/*, './SpiSequenceId')"!][!//
        [!VAR "SequenceName" = "node:name(.)"!][!//
        [!/* Find the core which current sequence mapped to */!][!//
        [!CALL "CG_FindSpiSequenceMappedCoreId", "SpiSequenceName" = "node:name(.)"!][!//
        [!LOOP "./SpiJobAssignment/*"!][!//
            [!/* Find the core which assigned job mapped to */!][!//
            [!VAR "CurrentJobName" = "text:split(., '/')[last()]"!][!//
            [!/* Find the core which current job mapped to */!]
            [!CALL "CG_FindSpiJobMappedCoreId", "SpiJobName" = "$CurrentJobName"!][!//
            /* If core mismatch between jobs and sequence */
            [!IF "$SpiSequenceMappedCoreId != num:i(255) and $SpiSequenceMappedCoreId != $SpiJobMappedCoreId"!][!//
                [!ERROR!][!//
                    [083-00-23-ERROR]: The Job [!"$CurrentJobName"!] assigned to [!"$SequenceName"!] is mapped in core[!"$SpiJobMappedCoreId"!], but [!"$SequenceName"!] is mapped in Core[!"$SpiSequenceMappedCoreId"!]. All jobs allocated to the same sequence must belong to one core.
                [!ENDERROR!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!//
    [!/***      Check whether all channels assigned to same job belong to the same core      ***/!][!//
    [!LOOP "node:order(SpiDriver/SpiJob/*, './SpiJobId')"!][!//
        [!/* Find the core which current job mapped to */!]
        [!CALL "CG_FindSpiJobMappedCoreId", "SpiJobName" = "node:name(../../.)"!][!//
        [!LOOP "node:order(SpiChannelList/*, './SpiChannelIndex')"!][!//
            [!/* Find the core which assigned channel mapped to */!][!//
            [!VAR "AssignedChannelName" = "text:split(./SpiChannelAssignment, '/')[last()]"!][!//
            [!CALL "CG_FindSpiChannelMappedCoreId", "SpiChannelName" = "$AssignedChannelName"!][!//
            /* If core mismatch between Channels and Job */
            [!IF "$SpiChannelMappedCoreId != $SpiJobMappedCoreId"!][!//
                [!/* Loop for find another jobs containing this channel*/!]
                [!ERROR!][!//
                    [!/* SWS_Spi_00370 A Channel is defined one time but it could belong to several Jobs according to the user needs and this software specification.*/!]
                    [083-00-24-ERROR]: The Channel [!"$AssignedChannelName"!] assigned to multiple jobs, but [!//
                    these Jobs is mapped in different Core.
                    [!"$AssignedChannelName"!] is Repeatedly mapped to [!//
                    [!LOOP "node:order(../../../*/SpiChannelList/*, './SpiChannelIndex')"!][!//
                        [!VAR "ModuleIndex" = "num:i(count(text:split(./SpiChannelAssignment, '/')))"!][!//
                        [!VAR "AssignedChannelNameFind" = "text:split(./SpiChannelAssignment, '/')[num:i($ModuleIndex)]"!][!//
                        [!IF "$AssignedChannelName = $AssignedChannelNameFind"!][!//
                            [!"node:name(../../.)"!]  [!//
                        [!ENDIF!][!//
                    [!ENDLOOP!]
                    Conclusion: A Channel can allocated to multiple jobs, but these jobs must belong to one core.
                [!ENDERROR!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/* Call CG_SpiAssignedConfigErrorDetect to detect the error */!]
[!CALL "CG_SpiAssignedConfigErrorDetect"!]

[!/*****************************************************************************
  MACRO: Spi_ChangeStrMember
    Object: StringList operation object, whose members are in the form of key-value pairs in the form of <key:KeyValue>
    Index : StringList member subscript index value
    Value : ''    : Perform +1 processing on the member with index in Object
            $Value: Use "$Value" to replace the indexed member in Object
*****************************************************************************/!]
[!MACRO "Spi_ChangeStrMember", "Object" = "", "Index" = "", "Value" = ""!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "KeyValue" = "substring-after(text:split($Object)[num:i($Index + 1)], ':')"!][!//
    [!VAR "BeforeString" = "concat($Index, ':', $KeyValue, ' ')"!][!/* CoreId:Num--->1:2 */!][!//
    [!IF "$Value = ''"!][!//
        [!VAR "AfterString"  = "concat($Index, ':', num:i($KeyValue + 1), ' ')"!][!/* CoreId:Num--->1:3 */!][!//
    [!ELSE!][!//
        [!VAR "AfterString"  = "concat($Index, ':', num:i($Value), ' ')"!][!/* CoreId:Num--->1:3 */!][!//
    [!ENDIF!][!//
    [!VAR "ReturnObject" = "text:replace($Object, $BeforeString, $AfterString)"!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_FindTotalNumSpiHwUnitMappedToCorex
  Find the number of hardware units used by each core
*****************************************************************************/!]
[!MACRO "CG_FindTotalNumSpiHwUnitMappedToCorex"!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "SpiHwUnitMappedCorex" = "''"!][!//
    [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        [!VAR "SpiHwUnitMappedCorex" = "concat($SpiHwUnitMappedCorex, $CoreIndex, ':0 ')"!][!//
    [!ENDFOR!][!//
    [!LOOP "node:order(SpiDriver/SpiHwUnitConfig/*, './SpiHWUnitMapping')"!][!//
        [!CALL "CG_FindSpiHwUnitMappedCoreId", "SpiHwUnitName"="node:name(.)"!][!//
        [!IF "$SpiHwUnitMappedCoreId != num:i(255)"!][!//
            [!CALL "Spi_ChangeStrMember", "Object"="$SpiHwUnitMappedCorex", "Index" = "$SpiHwUnitMappedCoreId", "Value" = "''"!][!//
            [!VAR "SpiHwUnitMappedCorex" = "$ReturnObject"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/* Call CG_FindTotalNumSpiHwUnitMappedToCorex here, Spi_PBCfg.c and Spi_Cfg.h can used variables */!][!//
[!CALL "CG_FindTotalNumSpiHwUnitMappedToCorex"!]
[!/*****************************************************************************
  MACRO: CG_FindTotalNumSpiExternalDeviceHwUnitMappedToCorex
  Find the number of external devices used by each core
*****************************************************************************/!]
[!MACRO "CG_FindTotalNumSpiExternalDeviceHwUnitMappedToCorex"!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "SpiExDeviceMappedCorex" = "''"!][!//
    [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        [!VAR "SpiExDeviceMappedCorex" = "concat($SpiExDeviceMappedCorex, $CoreIndex, ':0 ')"!][!//
    [!ENDFOR!][!//
    [!LOOP "node:order(SpiDriver/SpiExternalDevice/*, './SpiExternalDeviceId')"!][!//
        [!CALL "CG_FindSpiExternalDeviceMappedCoreId", "SpiExternalDeviceName"="node:name(.)"!][!//
        [!IF "$SpiExternalDeviceMappedCoreId != num:i(255)"!][!//
            [!CALL "Spi_ChangeStrMember", "Object"="$SpiExDeviceMappedCorex", "Index" = "$SpiExternalDeviceMappedCoreId", "Value" = "''"!][!//
            [!VAR "SpiExDeviceMappedCorex" = "$ReturnObject"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/* Call CG_FindTotalNumSpiExternalDeviceHwUnitMappedToCorex here, Spi_PBCfg.c and Spi_Cfg.h can used variables */!][!//
[!CALL "CG_FindTotalNumSpiExternalDeviceHwUnitMappedToCorex"!]
[!/*****************************************************************************
  MACRO: CG_FindTotalNumSpiChannelMappedToCorex
  Find the number of channels used by each core
*****************************************************************************/!]
[!MACRO "CG_FindTotalNumSpiChannelMappedToCorex"!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "SpiChannelMappedCorex" = "''"!][!//
    [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        [!VAR "SpiChannelMappedCorex" = "concat($SpiChannelMappedCorex, $CoreIndex, ':0 ')"!][!//
    [!ENDFOR!][!//
    [!LOOP "node:order(SpiDriver/SpiChannel/*, './SpiChannelId')"!][!//
        [!CALL "CG_FindSpiChannelMappedCoreId", "SpiChannelName"="node:name(.)"!][!//
        [!IF "$SpiChannelMappedCoreId != num:i(255)"!][!//
            [!CALL "Spi_ChangeStrMember", "Object"="$SpiChannelMappedCorex", "Index" = "$SpiChannelMappedCoreId", "Value" = "''"!][!//
            [!VAR "SpiChannelMappedCorex" = "$ReturnObject"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/* Call CG_FindTotalNumSpiChannelMappedToCorex here, Spi_PBCfg.c and Spi_Cfg.h can used variables */!][!//
[!CALL "CG_FindTotalNumSpiChannelMappedToCorex"!]
[!/*****************************************************************************
  MACRO: CG_FindTotalNumSpiJobMappedToCorex
  Find the number of jobs used by each core
*****************************************************************************/!]
[!MACRO "CG_FindTotalNumSpiJobMappedToCorex"!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "SpiJobMappedCorex" = "''"!][!//
    [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        [!VAR "SpiJobMappedCorex" = "concat($SpiJobMappedCorex, $CoreIndex, ':0 ')"!][!//
    [!ENDFOR!][!//
    [!LOOP "node:order(SpiDriver/SpiJob/*, './SpiJobId')"!][!//
        [!CALL "CG_FindSpiJobMappedCoreId", "SpiJobName"="node:name(.)"!][!//
        [!IF "$SpiJobMappedCoreId != num:i(255)"!][!//
            [!CALL "Spi_ChangeStrMember", "Object"="$SpiJobMappedCorex", "Index" = "$SpiJobMappedCoreId", "Value" = "''"!][!//
            [!VAR "SpiJobMappedCorex" = "$ReturnObject"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/* Call CG_FindTotalNumSpiJobMappedToCorex here, Spi_PBCfg.c and Spi_Cfg.h can used variables */!][!//
[!CALL "CG_FindTotalNumSpiJobMappedToCorex"!]
[!/*****************************************************************************
  MACRO: CG_FindTotalNumSpiSequenceMappedToCorex
  Find the number of sequences used by each core
*****************************************************************************/!]
[!MACRO "CG_FindTotalNumSpiSequenceMappedToCorex"!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "SpiSeqMappedCorex" = "''"!][!//
    [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        [!VAR "SpiSeqMappedCorex" = "concat($SpiSeqMappedCorex, $CoreIndex, ':0 ')"!][!//
    [!ENDFOR!][!//
    [!LOOP "node:order(SpiDriver/SpiSequence/*, './SpiSequenceId')"!][!//
        [!CALL "CG_FindSpiSequenceMappedCoreId", "SpiSequenceName"="node:name(.)"!][!//
        [!IF "$SpiSequenceMappedCoreId != num:i(255)"!][!//
            [!CALL "Spi_ChangeStrMember", "Object"="$SpiSeqMappedCorex", "Index" = "$SpiSequenceMappedCoreId", "Value" = "''"!][!//
            [!VAR "SpiSeqMappedCorex" = "$ReturnObject"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/* Call CG_FindTotalNumSpiSequenceMappedToCorex here, Spi_PBCfg.c and Spi_Cfg.h can used variables */!][!//
[!CALL "CG_FindTotalNumSpiSequenceMappedToCorex"!]
[!/*****************************************************************************
  MACRO: CG_GenerateDmaEnableMacro
  Generate the macro definition whether enable Customer CS
*****************************************************************************/!]
[!MACRO "CG_GenerateDmaEnableMacro"!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "SpiUseDmaMaskMappedCorex" = "''"!][!//
    [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        [!VAR "SpiUseDmaMaskMappedCorex" = "concat($SpiUseDmaMaskMappedCorex, $CoreIndex, ':false ')"!][!//
    [!ENDFOR!][!//
    [!LOOP "node:order(SpiDriver/SpiHwUnitConfig/*, './SpiHWUnitMapping')"!][!//
            [!CALL "CG_FindSpiHwUnitMappedCoreId", "SpiHwUnitName"="node:name(.)"!][!//
            [!VAR "TempSpiUseDmaMaskMappedCorex" = "text:split($SpiUseDmaMaskMappedCorex)[num:i($SpiHwUnitMappedCoreId + 1)]"!][!/* CoreId:Num--->1:false */!][!//
            [!IF "node:value(SpiEnableDMA) = 'true'
                  and contains($TempSpiUseDmaMaskMappedCorex, 'false')
                  and $SpiHwUnitMappedCoreId != num:i(255)"!][!//
                [!VAR "AfterString"  = "concat($SpiHwUnitMappedCoreId, ':', 'true', ' ')"!][!/* CoreId:Num--->1:true */!][!//
                [!VAR "SpiUseDmaMaskMappedCorex" = "text:replace($SpiUseDmaMaskMappedCorex, $TempSpiUseDmaMaskMappedCorex, $AfterString)"!][!//
            [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!CALL "CG_GenerateDmaEnableMacro"!][!//
[!/**************************************************************************************************
**                                        Generate IB buffer                                       **
*****************************************************************************************************/!][!//
[!/*****************************************************************************
  MACRO: CG_GenerateMaxChNumUsedByPhyUint
  Count the maximum number of channels bound to the SPI hardware using DMA transfer
*****************************************************************************/!]
[!MACRO "CG_GenerateMaxChNumUsedByPhyUint"!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "SpiMaxChNumUsedByPhyUintx" = "''"!][!//
    [!FOR "PhyUintNum" = "0" TO "num:i(ecu:get('Spi.MaxHwUnit') - 1)"!][!//
        [!VAR "SpiMaxChNumUsedByPhyUintx" = "concat($SpiMaxChNumUsedByPhyUintx, $PhyUintNum, ':0 ')"!][!//
    [!ENDFOR!][!//
    [!LOOP "node:order(SpiDriver/SpiJob/*, './SpiJobId')"!][!//
        [!IF "node:value(node:ref(node:ref(./SpiDeviceAssignment)/SpiHwUnitRef)/SpiEnableDMA) = 'true'"!][!//
            [!VAR "PhyUintID" = "num:i(text:split(node:ref(node:ref(./SpiDeviceAssignment)/SpiHwUnitRef)/SpiHWUnitMapping, '_')[last()])"!][!//
            [!VAR "NewTotalChannelUsePhyUintx" = "num:i(count(./SpiChannelList/*))"!][!//
            [!VAR "OldTotalChannelNumInJob" = "substring-after(text:split($SpiMaxChNumUsedByPhyUintx)[num:i($PhyUintID + 1)], ':')"!][!/* PhyUintId:Num--->1:2 */!][!//
            [!IF "num:i($OldTotalChannelNumInJob) < $NewTotalChannelUsePhyUintx"!][!//
                [!CALL "Spi_ChangeStrMember", "Object"="$SpiMaxChNumUsedByPhyUintx", "Index" = "$PhyUintID", "Value" = "$NewTotalChannelUsePhyUintx"!][!//
                [!VAR "SpiMaxChNumUsedByPhyUintx" = "$ReturnObject"!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!CALL "CG_GenerateMaxChNumUsedByPhyUint"!][!//
[!/*****************************************************************************
  MACRO: CG_GenerateEBIBEBbuffer
  Find the number of channels used by each core
*****************************************************************************/!]
[!MACRO "CG_GenerateEBIBEBbuffer"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "SpiChannelNumCorex" = "num:i(substring-after(text:split($SpiChannelMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
    [!VAR "SpiUseDmaMaskCorex" = "substring-after(text:split($SpiUseDmaMaskMappedCorex)[num:i($CoreIndex + 1)], ':')"!][!/* CoreId:Num--->1:false */!][!//
    [!/* Some channel(s) are mapped to specified core */!][!//
    [!IF "$SpiChannelNumCorex != num:i(0)"!][!//
        /* #Violation: Spi_PBcfg_c_REF_1 */
        #define SPI_START_SEC_VAR_CLEARED_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
        /* #Violation: Spi_PBcfg_c_REF_4 */
        #include "Spi_MemMap.h"

        [!IF "$SpiUseDmaMaskCorex"!][!//
            [!LOOP "node:order(SpiDriver/SpiHwUnitConfig/*, './SpiHWUnitMapping')"!][!//
                [!CALL "CG_FindSpiHwUnitMappedCoreId", "SpiHwUnitName"="node:name(.)"!][!//
                [!VAR "PhyUintID" = "num:i(text:split(./SpiHWUnitMapping, '_')[last()])"!][!//
                [!VAR "MaxChNumUsedByPhyUintx" = "substring-after(text:split($SpiMaxChNumUsedByPhyUintx)[num:i($PhyUintID + 1)], ':')"!][!/* PhyUintId:Num--->1:3 */!][!//
                [!IF "num:i($SpiHwUnitMappedCoreId) = $CoreIndex and $MaxChNumUsedByPhyUintx != num:i(0)"!][!//
                    /* Spi_[!"$PhyUintID"!] DMA linked list Channel dynamic configuration information storage buffer */
                    static uint32                    Spi_ChDynamicCfgBufferPhyUint[!"$PhyUintID"!][[!"$MaxChNumUsedByPhyUintx"!]];
                    /* Spi_[!"$PhyUintID"!] DMA linked list node storage buffer */
                    static Dma_LliBufType            Spi_DmaTcsBufferPhyUint[!"$PhyUintID"!][[!"num:i($MaxChNumUsedByPhyUintx * 3)"!]];
                    [!/* Line feed */!]
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
        /*SWS_Spi_00052:
            [!WS "3"!]For the IB Channels, the Handler/Driver shall provide the buffering but it is not able to take
            [!WS "3"!]care of the consistency of the data in the buffer during transmission. The size of the Channel
            [!WS "3"!]buffer is fixed.
            [!WS "2"!]SWS_Spi_00438:
            [!WS "3"!]The Handler/Driver shall provide separate buffer for receive and transmit to ensure that transmitted
            [!WS "3"!]data are not overwritten by the receive data.
            [!WS "2"!]SWS_Spi_00053:
            [!WS "3"!]For EB Channels the application shall provide the buffering and shall take care of the consistency
            [!WS "3"!]of the data in the buffer during transmission.
        */
        [!/* Loop all channels */!][!//
        [!LOOP "node:order(SpiDriver/SpiChannel/*, './SpiChannelId')"!][!//
            [!CALL "CG_FindSpiChannelMappedCoreId", "SpiChannelName"="node:name(.)"!][!//
            [!IF "num:i($SpiChannelMappedCoreId) = $CoreIndex"!][!//
                [!/* Allocate Buffers for IB Channels */!][!//
                [!IF "SpiChannelType = 'IB'"!][!//
                    /* Allocate Buffers for IB Channel[!"num:i(SpiChannelId)"!] */
                    [!IF "SpiDataWidth <= num:i(8)"!][!//
                        /* Expand internal buffer aligned to uint8(buffer is uint8 and actual data also is uint8) */
                        static ALIGNED(4) Spi_DataBufferType        BufferTX_PB[!"name(.)"!][[!"num:i(SpiIbNBuffers)"!]];
                        static ALIGNED(4) Spi_DataBufferType        BufferRX_PB[!"name(.)"!][[!"num:i(SpiIbNBuffers)"!]];
                    [!ELSEIF "SpiDataWidth <= num:i(16)"!][!//
                        /* Expand internal buffer aligned to uint16(buffer is uint8 and actual data is uint16) */
                        static ALIGNED(4) Spi_DataBufferType        BufferTX_PB[!"name(.)"!][[!"num:i(SpiIbNBuffers * num:i(2))"!]];
                        static ALIGNED(4) Spi_DataBufferType        BufferRX_PB[!"name(.)"!][[!"num:i(SpiIbNBuffers * num:i(2))"!]];
                    [!ELSE!][!//
                        /* Expand internal buffer aligned to uint32(buffer is uint8 and actual data is uint32) */
                        static ALIGNED(4) Spi_DataBufferType        BufferTX_PB[!"name(.)"!][[!"num:i(SpiIbNBuffers * num:i(4))"!]];
                        static ALIGNED(4) Spi_DataBufferType        BufferRX_PB[!"name(.)"!][[!"num:i(SpiIbNBuffers * num:i(4))"!]];
                    [!ENDIF!][!//
                        [!/* Line feed */!]
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!//
        /* Record the length of the actual data to be transmitted on the channel (Byte) in core[!"$CoreIndex"!] */
        static Spi_NumberOfDataType      Spi_ChannelActualDataLengthCore[!"$CoreIndex"!][SPI_MAX_CHANNEL_CORE[!"$CoreIndex"!]];
        /* Job status management structure variables. */
        static Spi_JobStateType          Spi_JobStateCore[!"$CoreIndex"!][SPI_MAX_JOB_CORE[!"$CoreIndex"!]];

        /* #Violation: Spi_PBcfg_c_REF_1 */
        #define SPI_STOP_SEC_VAR_CLEARED_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
        /* #Violation: Spi_PBcfg_c_REF_4 */
        #include "Spi_MemMap.h"

        /* #Violation: Spi_PBcfg_c_REF_1 */
        #define SPI_START_SEC_VAR_INIT_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
        /* #Violation: Spi_PBcfg_c_REF_4 */
        #include "Spi_MemMap.h"

        [!LOOP "node:order(SpiDriver/SpiChannel/*, './SpiChannelId')"!][!//
            [!CALL "CG_FindSpiChannelMappedCoreId", "SpiChannelName"="node:name(.)"!][!//
            [!IF "num:i($SpiChannelMappedCoreId) = $CoreIndex"!][!//
                [!IF "SpiChannelType = 'IB'"!][!//
                    /* Buffers Descriptors for IB Channel[!"num:i(SpiChannelId)"!] */
                    static Spi_BufferDescriptorType  Buffer_PB[!"name(.)"!] =
                    {
                        [!INDENT "4"!][!//
                        /* Channel default Transmit Value. */
                        [!IF "node:exists(SpiDefaultData)"!][!//
                            [!IF "SpiDataWidth <= num:i(8)"!][!//
                                (uint32)0x[!"substring-after(text:toupper(num:inttohex(SpiDefaultData, 2)), 'X')"!]U,
                            [!ELSEIF "SpiDataWidth <= num:i(16)"!][!//
                                (uint32)0x[!"substring-after(text:toupper(num:inttohex(SpiDefaultData, 4)), 'X')"!]U,
                            [!ELSE!][!//
                                (uint32)0x[!"substring-after(text:toupper(num:inttohex(SpiDefaultData, 8)), 'X')"!]U,
                            [!ENDIF!][!//
                        [!ELSE!][!//
                            (uint32)0x55UL,
                        [!ENDIF!][!//
                        /* Tx buffer address pointer */
                        BufferTX_PB[!"name(.)"!],
                        /* Rx buffer address pointer */
                        BufferRX_PB[!"name(.)"!]
                        [!ENDINDENT!][!//
                    };
                [!ELSE!][!//
                    /* Buffers Descriptors for EB Channel[!"num:i(SpiChannelId)"!] */
                    static Spi_BufferDescriptorType  Buffer_PB[!"name(.)"!] =
                    {
                        [!INDENT "4"!][!//
                        /* Channel default Transmit Value. */
                        [!IF "node:exists(SpiDefaultData)"!][!//
                            [!IF "SpiDataWidth <= num:i(8)"!][!//
                                (uint32)0x[!"substring-after(text:toupper(num:inttohex(SpiDefaultData, 2)), 'X')"!]U,
                            [!ELSEIF "SpiDataWidth <= num:i(16)"!][!//
                                (uint32)0x[!"substring-after(text:toupper(num:inttohex(SpiDefaultData, 4)), 'X')"!]U,
                            [!ELSE!][!//
                                (uint32)0x[!"substring-after(text:toupper(num:inttohex(SpiDefaultData, 8)), 'X')"!]U,
                            [!ENDIF!][!//
                        [!ELSE!][!//
                            (uint32)0x55UL,
                        [!ENDIF!][!//
                        /* Tx buffer address pointer */
                        NULL_PTR,
                         /* Rx buffer address pointer */
                        NULL_PTR
                        [!ENDINDENT!][!//
                    };
                [!ENDIF!][!//
                [!/* Line feed */!]
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        /* #Violation: Spi_PBcfg_c_REF_1 */
        #define SPI_STOP_SEC_VAR_INIT_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
        /* #Violation: Spi_PBcfg_c_REF_4 */
        #include "Spi_MemMap.h"
        [!/* Line feed */!]
    [!ENDIF!][!//
[!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**************************************************************************************************
**    Generate HwUnit, ExternalDeviceHwUnit, Channel, Job, Sequence configuration information      **
*****************************************************************************************************/!][!//
[!/*****************************************************************************
  MACRO: CG_GenerateHwUnitDynamicConfig
  Generate HwUnit configuration
*****************************************************************************/!]
[!MACRO "CG_GenerateHwUnitDynamicConfig"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!VAR "FoundDynHwUnitlCnt" = "0"!][!//
[!LOOP "node:order(SpiDriver/SpiHwUnitConfig/*, './SpiHWUnitMapping')"!][!//
    [!CALL "CG_FindSpiHwUnitMappedCoreId", "SpiHwUnitName"="node:name(.)"!][!//
    [!IF "num:i($SpiHwUnitMappedCoreId) = $CoreIndex"!][!//
        [!VAR "FoundDynHwUnitlCnt" = "$FoundDynHwUnitlCnt + 1"!][!//
        [!INDENT "4"!][!//
        {
            [!INDENT "8"!][!//
            /* [!"node:name(.)"!] use Espi HwUnit:E[!"./SpiHWUnitMapping"!]*/
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
            [!"SpiGlobalClkDivRatioParamTq"!]U,
            /* Enable/Disable SPI TX/RX DMA */
            [!"text:toupper(node:value(./SpiEnableDMA))"!],
            /* Enable Move Counter Mode */
            TRUE
            [!ENDINDENT!][!//
        }[!IF "num:i($FoundDynHwUnitlCnt) < $SpiHwUnitNumCorex"!],[!ENDIF!]
        [!ENDINDENT!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GenerateHwUnitConfig
  Generate Spi HwUnit configuration
*****************************************************************************/!]
[!MACRO "CG_GenerateHwUnitConfig"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!VAR "FoundHwUnitCnt" = "0"!][!//
    [!VAR "SpiHwUnitExistFlag" = "0"!][!//
    [!LOOP "node:order(SpiDriver/SpiHwUnitConfig/*, './SpiHWUnitMapping')"!][!//
        [!CALL "CG_FindSpiHwUnitMappedCoreId", "SpiHwUnitName" = "node:name(.)"!][!//
        [!IF "$SpiHwUnitMappedCoreId = $CoreIndex"!][!//
            [!VAR "SpiHwUnitID" = "substring-after(./SpiHWUnitMapping,'Spi_')"!][!//
            [!VAR "FoundHwUnitCnt" = "$FoundHwUnitCnt + num:i(1)"!][!//
            [!INDENT "4"!][!//
            {
                [!INDENT "8"!][!//
                    /* Spi number is: Spi[!"$SpiHwUnitID"!]  */
                    (uint8)[!"num:i($SpiHwUnitID)"!]U,
                    [!IF "contains($SpiUseDmaMaskMappedCorex, 'true')"!][!//
                        [!IF "./SpiEnableDMA = 'true'"!][!//
                            /* Defines the TX DMA Channel ID referenced by the Spi HwUnit */
                            [!"node:value(node:ref(./SpiTxDmaChannelRef)/DmaChannelId)"!]U,
                            /* Defines the RX DMA Channel ID referenced by the Spi HwUnit */
                            [!"node:value(node:ref(./SpiRxDmaChannelRef)/DmaChannelId)"!]U,
                            /* Pointer DMA linked list Channel dynamic configuration information storage buffer */
                            &Spi_ChDynamicCfgBufferPhyUint[!"$SpiHwUnitID"!][0],
                            /* Points to the DMA linked list TCS storage buffer */
                            &Spi_DmaTcsBufferPhyUint[!"$SpiHwUnitID"!][0],
                        [!ELSE!][!//
                            /* Defines the TX DMA Channel ID referenced by the Spi HwUnit */
                            0xFFU,
                            /* Defines the RX DMA Channel ID referenced by the Spi HwUnit */
                            0xFFU,
                            /* Pointer DMA linked list Channel dynamic configuration information storage buffer */
                            NULL_PTR,
                            /* Points to the DMA linked list TCS storage buffer */
                            NULL_PTR,
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    /* SPI HwUnit configuration parameter structure */
                    &Spi_PhyUnitConfigParamCore[!"$CoreIndex"!][[!"num:i(num:i($FoundHwUnitCnt)-num:i(1))"!]]
                [!ENDINDENT!][!//
            }[!IF "num:i($FoundHwUnitCnt) < $SpiHwUnitNumCorex"!],[!ENDIF!]
            [!ENDINDENT!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************
MACRO: CG_AutoCalcBaudParams
Macro to Calculate the baudrate and delay params
******************************************************************************/!]
[!MACRO "CG_AutoCalcBaudParams", "ExternalDevice" = ""!][!//
[!//
[!NOCODE!][!//

[!SELECT "as:modconf('Spi')[1]/SpiDriver/SpiExternalDevice/*[node:name(.) = $ExternalDevice]"!][!//
    [!/******** Baudrate Calculation **********/!][!//
    [!VAR "SpiSystemClockFreq"="num:i(node:value(node:ref(./SpiModuleClock)/McuClockReferencePointFrequency))"!][!//
    [!VAR "SpiBaudParamA"="num:i(1)"!][!//
    [!VAR "SpiBaudParamB"="num:i(0)"!][!//
    [!VAR "SpiBaudParamC"="num:i(0)"!][!//
    [!VAR "SpiBaudParamQ"="num:i(0)"!][!//
    [!VAR "SpiBaudParamTQ"="num:i(1)"!][!//
    [!VAR "SpiBaudParamABC"="num:i(2)"!][!//
    [!IF "node:value(./SpiAutoCalcBaudrateParams) = 'true'"!][!//
        [!VAR "SpiBaudRateValue"="num:i(node:value(./SpiBaudrate))"!][!//
        [!VAR "SpiBaudParamTQ"="num:i(node:value(node:ref(./SpiHwUnitRef)/SpiGlobalClkDivRatioParamTq))"!][!//
        [!VAR "LoopBreakFlag"="num:i(0)"!][!//
        [!IF "num:i(640 * num:i($SpiBaudParamTQ) * num:i($SpiBaudRateValue)) < num:i($SpiSystemClockFreq)"!][!//
            [!ERROR!][!//
                [083-00-29-ERROR]: Autocalculation for the spcified baudrate([!"$SpiBaudRateValue"!]Hz) is too small, could not be done for the given frequence(SpiModuleClock = [!"$SpiSystemClockFreq"!]Hz)
            [!ENDERROR!][!//
        [!ENDIF!][!//
        [!IF "num:i(2 * num:i($SpiBaudParamTQ) * num:i($SpiBaudRateValue)) > num:i($SpiSystemClockFreq)"!][!//
            [!ERROR!][!//
                [083-00-30-ERROR]: Autocalculation for the spcified baudrate([!"$SpiBaudRateValue"!]Hz) is too large, it could not be done for the given frequence(SpiModuleClock = [!"$SpiSystemClockFreq"!]Hz)
            [!ENDERROR!][!//
        [!ENDIF!][!//
        [!/* The Config value of parameter Q is 1~64(0x3F) */!][!//
        [!FOR "SpiBaudParamQ"="1" TO "64"!][!//
            [!/* If C=0 and B=0, default A =2, So SpiBaudParamABC is 2~10 */!][!//
            [!FOR "SpiBaudParamABC"="num:i(2)" TO "num:i(10)"!][!//
                [!/* Hardware requirements:Q*(A+B+C) >= 2 */!][!//
                [!IF "($SpiBaudParamQ  * $SpiBaudParamABC) >= num:i(2)"!][!//
                    [!IF "($SpiBaudParamABC * $SpiBaudRateValue * $SpiBaudParamQ * $SpiBaudParamTQ) > $SpiSystemClockFreq"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                    [!/* The Config value of parameter TQ is 0~255(0xFF) */!][!//
                        [!/* Calculate system clock frequency based on current parameters */!][!//
                        [!VAR "SpiSystemClockFreqTemp"="num:i($SpiBaudParamABC * $SpiBaudRateValue * $SpiBaudParamTQ * $SpiBaudParamQ)"!][!//
                        [!IF "$SpiSystemClockFreqTemp = $SpiSystemClockFreq"!][!//
                            [!/* Baud rate calculated successfully, Set Flag, Success: jumping out of the current FOR loop */!][!//
                            [!VAR "LoopBreakFlag"="1"!][!//
                            [!BREAK!][!//
                        [!ELSEIF "$SpiSystemClockFreqTemp > $SpiSystemClockFreq"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!/* Check calculation success flag, Success: jumping out of the current FOR loop */!][!//
                    [!IF "num:i($LoopBreakFlag)=num:i(1)"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!/* Check calculation success flag, Success: jumping out of the current FOR loop */!][!//
            [!IF "num:i($LoopBreakFlag)=num:i(1)"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
        [!/* Check calculation success flag, Fail: report error */!][!//
        [!IF "num:i($LoopBreakFlag)=num:i(0)"!][!//
            [!ERROR!][!//
                [083-00-25-ERROR]: Autocalculation for the spcified baudrate([!"$SpiBaudRateValue"!]Hz) could not be done for the given frequence(SpiModuleClock = [!"$SpiSystemClockFreq"!]Hz)
            [!ENDERROR!][!//
        [!ENDIF!][!//
        [!VAR "LoopBreakFlag"="0"!][!//
        [!FOR "SpiBaudParamA"="num:i(1)" TO "num:i(4)"!][!//
            [!FOR "SpiBaudParamB"="num:i(0)" TO "num:i(3)"!][!//
                [!FOR "SpiBaudParamC"="num:i(0)" TO "num:i(3)"!][!//
                    [!IF "$SpiBaudParamA + $SpiBaudParamB + $SpiBaudParamC = $SpiBaudParamABC"!][!//
                        [!VAR "LoopBreakFlag"="1"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDFOR!][!//
                [!IF "num:i($LoopBreakFlag)=num:i(1)"!][!//
                    [!BREAK!][!//
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!IF "num:i($LoopBreakFlag)=num:i(1)"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
    [!ELSE!][!//
        [!VAR "SpiBaudParamA"="num:i(node:value(./SpiBaudrateParams/*[1]/SpiBaudParamA))"!][!//
        [!VAR "SpiBaudParamB"="num:i(node:value(./SpiBaudrateParams/*[1]/SpiBaudParamB))"!][!//
        [!VAR "SpiBaudParamC"="num:i(node:value(./SpiBaudrateParams/*[1]/SpiBaudParamC))"!][!//
        [!VAR "SpiBaudParamTQ"="num:i(node:value(node:ref(./SpiHwUnitRef)/SpiGlobalClkDivRatioParamTq))"!][!//
        [!VAR "SpiBaudParamQ"="num:i(node:value(./SpiBaudrateParams/*[1]/SpiBaudParamQ))"!][!//
        [!IF "num:i($SpiBaudParamB + $SpiBaudParamC)=num:i(0)"!][!//
            [!VAR "SpiBaudRateValue"="num:i($SpiSystemClockFreq div ($SpiBaudParamTQ*$SpiBaudParamQ*($SpiBaudParamA + num:i(1))))"!][!//
        [!ELSE!][!//
            [!VAR "SpiBaudRateValue"="num:i($SpiSystemClockFreq div ($SpiBaudParamTQ*$SpiBaudParamQ*($SpiBaudParamA + $SpiBaudParamB + $SpiBaudParamC)))"!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!]
[!/*****************************************************************************
  MACRO: CG_GenerateExternalDeviceDynamicConfig
  Generate external device configuration
*****************************************************************************/!]
[!MACRO "CG_GenerateExternalDeviceDynamicConfig"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!VAR "FoundDynExDeviceCnt" = "0"!][!//
[!LOOP "node:order(SpiDriver/SpiExternalDevice/*, './SpiExternalDeviceId')"!][!//
    [!CALL "CG_FindSpiExternalDeviceMappedCoreId", "SpiExternalDeviceName"="node:name(.)"!][!//
    [!IF "num:i($SpiHwUnitMappedCoreId) = $CoreIndex"!][!//
        [!VAR "FoundDynExDeviceCnt" = "$FoundDynExDeviceCnt + 1"!][!//
        [!CALL "CG_AutoCalcBaudParams", "ExternalDevice"="node:name(.)"!][!//
        [!INDENT "4"!][!//
        {
            [!INDENT "8"!][!//
            {
                [!INDENT "12"!][!//
                /*
                [!"node:name(.)"!]
                Baudrate parameter Tq is [!"num:i($SpiBaudParamTQ)"!]U.
                SpiModuleClock is [!"node:value(node:ref(./SpiModuleClock)/McuClockReferencePointFrequency)"!]
                Baudrate calculation formula:
                    if SpiBaudParamB+SpiBaudParamC  = 0U: Baudrate = SpiModuleClock / (Tq*Q*(A+1))
                    if SpiBaudParamB+SpiBaudParamC != 0U: Baudrate = SpiModuleClock / (Tq*Q*(A+B+C))
                Baudrate is [!"num:i($SpiBaudRateValue)"!]U.
                */
                /* Baudrate parameter A */
                [!IF "num:i($SpiBaudParamA) = num:i(1)"!][!//
                    ESPI_PARAMETER_A_ONE_UNIT,
                [!ELSEIF "num:i($SpiBaudParamA) = num:i(2)"!][!//
                    ESPI_PARAMETER_A_TWO_UNITS,
                [!ELSEIF "num:i($SpiBaudParamA) = num:i(3)"!][!//
                    ESPI_PARAMETER_A_THREE_UNITS,
                [!ELSE!][!//
                    ESPI_PARAMETER_A_FOUR_UNITS,
                [!ENDIF!][!//
                /* Baudrate parameter B */
                [!IF "num:i($SpiBaudParamB) = num:i(0)"!][!//
                    ESPI_PARAMETER_B_NONE,
                [!ELSEIF "num:i($SpiBaudParamB) = num:i(1)"!][!//
                    ESPI_PARAMETER_B_ONE_UNIT,
                [!ELSEIF "num:i($SpiBaudParamB) = num:i(2)"!][!//
                    ESPI_PARAMETER_B_TWO_UNITS,
                [!ELSE!][!//
                    ESPI_PARAMETER_B_THREE_UNITS,
                [!ENDIF!][!//
                /* Baudrate parameter C */
                [!IF "num:i($SpiBaudParamC) = num:i(0)"!][!//
                    ESPI_PARAMETER_C_NONE,
                [!ELSEIF "num:i($SpiBaudParamC) = num:i(1)"!][!//
                    ESPI_PARAMETER_C_ONE_UNIT,
                [!ELSEIF "num:i($SpiBaudParamC) = num:i(2)"!][!//
                    ESPI_PARAMETER_C_TWO_UNITS,
                [!ELSE!][!//
                    ESPI_PARAMETER_C_THREE_UNITS,
                [!ENDIF!][!//
                /* Baudrate parameter Q */
                [!"num:i($SpiBaudParamQ)"!]U
                [!ENDINDENT!][!//
            },
            /* Defines the SPI Idle clock level  */
            [!IF "./SpiShiftClockIdleLevel = 'LOW'"!][!//
                ESPI_CLOCKPOLARITY_IDLE_LOW,
            [!ELSE!][!//
                ESPI_CLOCKPOLARITY_IDLE_HIGH,
            [!ENDIF!][!//
            /* Defines the SPI data sampling edge */
            [!IF "./SpiDataShiftEdge = 'LEADING'"!][!//
                ESPI_CLOCKPHASE_SECONDSAMPLE,
            [!ELSE!][!//
                ESPI_CLOCKPHASE_FIRSTSAMPLE,
            [!ENDIF!][!//
            [!IF "./SpiParitySupport != 'Unused'"!][!//
                /* Defines Enable SPI parity check */
                TRUE,
            [!ELSE!][!//
                /* Defines disable SPI parity check */
                FALSE,
            [!ENDIF!][!//
            /* Defines SPI CS channel number */
            ESPI_CS_CHANNEL_ID_[!"text:split(./SpiCsIdentifier, '_')[last()]"!],
            /* Defines SPI CS active output level */
            [!IF "./SpiCsPolarity = 'LOW'"!][!//
                ESPI_SLSOOUTPUT_LEVEL_LOW,
            [!ELSE!][!//
                ESPI_SLSOOUTPUT_LEVEL_HIGH,
            [!ENDIF!][!//
            /* Define enable SPI internal chip select */
            [!IF "node:value(./SpiEnableCs) = 'true' and
                  node:exists(./SpiCsSelection) and
                  node:value(./SpiCsSelection) = 'CS_VIA_GPIO'"!][!//
                FALSE
            [!ELSE!][!//
                TRUE
            [!ENDIF!][!//
            [!ENDINDENT!][!//
        }[!IF "num:i($FoundDynExDeviceCnt) < $SpiExDeviceNumCorex"!],[!ENDIF!]
        [!ENDINDENT!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************
  MACRO: CG_GenerateExternalDeviceConfig
  Generate External Device configuration
*****************************************************************************/!]
[!MACRO "CG_GenerateExternalDeviceConfig"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!VAR "FoundExDeviceCnt" = "0"!][!//
[!LOOP "node:order(SpiDriver/SpiExternalDevice/*, './SpiExternalDeviceId')"!][!//
    [!CALL "CG_FindSpiExternalDeviceMappedCoreId", "SpiExternalDeviceName"="node:name(.)"!][!//
    [!IF "$SpiExternalDeviceMappedCoreId = $CoreIndex"!][!//
        [!VAR "FoundExDeviceCnt" = "$FoundExDeviceCnt + 1"!][!//
        [!INDENT "4"!][!//
        {
            [!INDENT "8"!][!//
            [!VAR "SpiHwUnitID"="substring-after(node:value(node:ref(./SpiHwUnitRef)/SpiHWUnitMapping),'Spi_')"!][!//
            /* [!"node:name(.)"!] use Espi HwUnit: Espi[!"($SpiHwUnitID)"!] */
            (Spi_HWUnitType)[!"$SpiHwUnitID"!]U,
            /* The chip select */
            [!IF "node:value(SpiEnableCs) = 'true' and node:exists(SpiCsSelection)"!]SPI_[!"SpiCsSelection"!],[!ELSE!]SPI_CS_VIA_PERIPHERAL_ENGINE,[!ENDIF!]
            /* Variable to restore Gpio CS pin. */
            [!IF "./SpiEnableCs = 'true' and ./SpiCsSelection = 'CS_VIA_GPIO'"!][!//
                (uint16)[!"num:i(node:value(node:ref(SpiCustomCsPinRef)/../../DioPortId) * num:i(16) + node:value(node:ref(SpiCustomCsPinRef)/DioChannelId))"!]U,
            [!ELSE!][!//
                (uint16)0xFFU,    /* Dio is not used as the chip selector */
            [!ENDIF!][!//
            [!IF "./SpiParitySupport = 'Unused'"!][!//
                /* Parity: NONE, Not using parity */
                ESPI_PARITYMODE_NONE,
            [!ELSE!][!//
                /* Parity: [!"text:toupper(SpiParitySupport)"!] */
                ESPI_PARITYMODE_[!"text:toupper(SpiParitySupport)"!],
            [!ENDIF!][!//
            [!CALL "CG_AutoCalcDelayParams", "ExternalDevice"="node:name(.)"!][!//
            /* Delay parameters */
            {
                /* SpiModuleClock is [!"node:value(node:ref(./SpiModuleClock)/McuClockReferencePointFrequency)"!] */
                [!INDENT "12"!][!//
                {
                    /* SpiTrailingTime =  (SpiParamTrailUnit + 1) * 4^SpiParamTrail / SpiModuleClock */
                    [!INDENT "16"!][!//
                    [!IF "num:i($SpiDelayParamTrail) = num:i(0)"!][!//
                        ESPI_DELAY_PRESCALER_1,
                    [!ELSEIF "num:i($SpiDelayParamTrail) = num:i(1)"!][!//
                        ESPI_DELAY_PRESCALER_4,
                    [!ELSEIF "num:i($SpiDelayParamTrail) = num:i(2)"!][!//
                        ESPI_DELAY_PRESCALER_16,
                    [!ELSEIF "num:i($SpiDelayParamTrail) = num:i(3)"!][!//
                        ESPI_DELAY_PRESCALER_64,
                    [!ELSEIF "num:i($SpiDelayParamTrail) = num:i(4)"!][!//
                        ESPI_DELAY_PRESCALER_256,
                    [!ELSEIF "num:i($SpiDelayParamTrail) = num:i(5)"!][!//
                        ESPI_DELAY_PRESCALER_1024,
                    [!ELSEIF "num:i($SpiDelayParamTrail) = num:i(6)"!][!//
                        ESPI_DELAY_PRESCALER_4096,
                    [!ELSE!][!//
                        ESPI_DELAY_PRESCALER_16384,
                    [!ENDIF!][!//
                    [!IF "num:i($SpiDelayParamTrailUnits) = num:i(0)"!][!//
                        ESPI_DELAY_UNIT_1
                    [!ELSEIF "num:i($SpiDelayParamTrailUnits) = num:i(1)"!][!//
                        ESPI_DELAY_UNIT_2
                    [!ELSEIF "num:i($SpiDelayParamTrailUnits) = num:i(2)"!][!//
                        ESPI_DELAY_UNIT_3
                    [!ELSEIF "num:i($SpiDelayParamTrailUnits) = num:i(3)"!][!//
                        ESPI_DELAY_UNIT_4
                    [!ELSEIF "num:i($SpiDelayParamTrailUnits) = num:i(4)"!][!//
                        ESPI_DELAY_UNIT_5
                    [!ELSEIF "num:i($SpiDelayParamTrailUnits) = num:i(5)"!][!//
                        ESPI_DELAY_UNIT_6
                    [!ELSEIF "num:i($SpiDelayParamTrailUnits) = num:i(6)"!][!//
                        ESPI_DELAY_UNIT_7
                    [!ELSE!][!//
                        ESPI_DELAY_UNIT_8
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                },
                {
                    /* SpiTimeClk2Cs =  (SpiDelayParamLeadUnits + 1) * 4^SpiDelayParamLead / SpiModuleClock */
                    [!INDENT "16"!][!//
                    [!IF "num:i($SpiDelayParamLead) = num:i(0)"!][!//
                        ESPI_DELAY_PRESCALER_1,
                    [!ELSEIF "num:i($SpiDelayParamLead) = num:i(1)"!][!//
                        ESPI_DELAY_PRESCALER_4,
                    [!ELSEIF "num:i($SpiDelayParamLead) = num:i(2)"!][!//
                        ESPI_DELAY_PRESCALER_16,
                    [!ELSEIF "num:i($SpiDelayParamLead) = num:i(3)"!][!//
                        ESPI_DELAY_PRESCALER_64,
                    [!ELSEIF "num:i($SpiDelayParamLead) = num:i(4)"!][!//
                        ESPI_DELAY_PRESCALER_256,
                    [!ELSEIF "num:i($SpiDelayParamLead) = num:i(5)"!][!//
                        ESPI_DELAY_PRESCALER_1024,
                    [!ELSEIF "num:i($SpiDelayParamLead) = num:i(6)"!][!//
                        ESPI_DELAY_PRESCALER_4096,
                    [!ELSE!][!//
                        ESPI_DELAY_PRESCALER_16384,
                    [!ENDIF!][!//
                    [!IF "num:i($SpiDelayParamLeadUnits) = num:i(0)"!][!//
                        ESPI_DELAY_UNIT_1
                    [!ELSEIF "num:i($SpiDelayParamLeadUnits) = num:i(1)"!][!//
                        ESPI_DELAY_UNIT_2
                    [!ELSEIF "num:i($SpiDelayParamLeadUnits) = num:i(2)"!][!//
                        ESPI_DELAY_UNIT_3
                    [!ELSEIF "num:i($SpiDelayParamLeadUnits) = num:i(3)"!][!//
                        ESPI_DELAY_UNIT_4
                    [!ELSEIF "num:i($SpiDelayParamLeadUnits) = num:i(4)"!][!//
                        ESPI_DELAY_UNIT_5
                    [!ELSEIF "num:i($SpiDelayParamLeadUnits) = num:i(5)"!][!//
                        ESPI_DELAY_UNIT_6
                    [!ELSEIF "num:i($SpiDelayParamLeadUnits) = num:i(6)"!][!//
                        ESPI_DELAY_UNIT_7
                    [!ELSE!][!//
                        ESPI_DELAY_UNIT_8
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                },
                {
                    /* SpiIdleTime =  (SpiDelayParamIdleUnits + 1) * 4^SpiDelayParamIdle / SpiModuleClock */
                    [!INDENT "16"!][!//
                    [!IF "num:i($SpiDelayParamIdle) = num:i(0)"!][!//
                        ESPI_DELAY_PRESCALER_1,
                    [!ELSEIF "num:i($SpiDelayParamIdle) = num:i(1)"!][!//
                        ESPI_DELAY_PRESCALER_4,
                    [!ELSEIF "num:i($SpiDelayParamIdle) = num:i(2)"!][!//
                        ESPI_DELAY_PRESCALER_16,
                    [!ELSEIF "num:i($SpiDelayParamIdle) = num:i(3)"!][!//
                        ESPI_DELAY_PRESCALER_64,
                    [!ELSEIF "num:i($SpiDelayParamIdle) = num:i(4)"!][!//
                        ESPI_DELAY_PRESCALER_256,
                    [!ELSEIF "num:i($SpiDelayParamIdle) = num:i(5)"!][!//
                        ESPI_DELAY_PRESCALER_1024,
                    [!ELSEIF "num:i($SpiDelayParamIdle) = num:i(6)"!][!//
                        ESPI_DELAY_PRESCALER_4096,
                    [!ELSE!][!//
                        ESPI_DELAY_PRESCALER_16384,
                    [!ENDIF!][!//
                    [!IF "num:i($SpiDelayParamIdleUnits) = num:i(0)"!][!//
                        ESPI_DELAY_UNIT_1
                    [!ELSEIF "num:i($SpiDelayParamIdleUnits) = num:i(1)"!][!//
                        ESPI_DELAY_UNIT_2
                    [!ELSEIF "num:i($SpiDelayParamIdleUnits) = num:i(2)"!][!//
                        ESPI_DELAY_UNIT_3
                    [!ELSEIF "num:i($SpiDelayParamIdleUnits) = num:i(3)"!][!//
                        ESPI_DELAY_UNIT_4
                    [!ELSEIF "num:i($SpiDelayParamIdleUnits) = num:i(4)"!][!//
                        ESPI_DELAY_UNIT_5
                    [!ELSEIF "num:i($SpiDelayParamIdleUnits) = num:i(5)"!][!//
                        ESPI_DELAY_UNIT_6
                    [!ELSEIF "num:i($SpiDelayParamIdleUnits) = num:i(6)"!][!//
                        ESPI_DELAY_UNIT_7
                    [!ELSE!][!//
                        ESPI_DELAY_UNIT_8
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                }
                [!ENDINDENT!][!//
            },
            /* External device configuration parameter structure */
            &SpiExternalDevice_ConfigParamCore[!"$CoreIndex"!][[!"num:i($FoundExDeviceCnt - 1)"!]]
            [!ENDINDENT!][!//
        }[!IF "$FoundExDeviceCnt < $SpiExDeviceNumCorex"!],[!ENDIF!]
        [!ENDINDENT!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************
  MACRO: CG_GenerateChannelConfig
  Generate channel configuration
*****************************************************************************/!]
[!MACRO "CG_GenerateChannelConfig"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!/* Channel Configuration */!][!//
[!VAR "FoundChannelCnt" = "0"!][!//
[!LOOP "node:order(SpiDriver/SpiChannel/*, './SpiChannelId')"!][!//
    [!CALL "CG_FindSpiChannelMappedCoreId", "SpiChannelName"="node:name(.)"!][!//
    [!IF "num:i($SpiChannelMappedCoreId) = $CoreIndex"!][!//
        [!VAR "FoundChannelCnt" = "$FoundChannelCnt + 1"!][!//
        [!INDENT "4"!][!//
        {
            [!INDENT "8"!][!//
            /* SPI channel ID: [!"node:name(.)"!] */
            [!"SpiChannelId"!]U,
            /* Buffer Type IB/EB. */
            SPI_[!"SpiChannelType"!],
            /* SPI data width in channel */
            ESPI_DATAWIDTH_[!"SpiDataWidth"!],
            /* The number of bytes occupied by a data bits */
            [!IF "SpiDataWidth <= num:i(8)"!][!//
                ESPI_DATABUFFER_8BITS,
            [!ELSEIF "SpiDataWidth <= num:i(16)"!][!//
                ESPI_DATABUFFER_16BITS,
            [!ELSE!][!//
                ESPI_DATABUFFER_32BITS,
            [!ENDIF!][!//
            [!//
            [!IF "SpiChannelType = 'IB'"!][!//
                /* Data length. SpiIbNBuffers */
                [!"SpiIbNBuffers"!]U,
            [!ELSE!][!//
                /* Data length. SpiEbMaxLength */
                [!"SpiEbMaxLength"!]U,
            [!ENDIF!][!//
            /* Buffer Descriptor. */
            &Buffer_PB[!"name(.)"!],
            /* The length of the actual data to be transmitted on the channel (Byte). */
            &Spi_ChannelActualDataLengthCore[!"$CoreIndex"!][[!"num:i($FoundChannelCnt - 1)"!]],
            /* Defines the first starting bit for transmission */
            ESPI_BITORDER_[!"SpiTransferStart"!]
            [!ENDINDENT!][!//
        }[!IF "num:i($FoundChannelCnt) < $SpiChannelNumCorex"!],[!ENDIF!]
        [!ENDINDENT!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************
  MACRO: CG_GenerateJobConfig
  Generate Job configuration
*****************************************************************************/!]
[!MACRO "CG_GenerateJobConfig"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!/* level Configuration */!][!//
[!VAR "Level" = "num:i(SpiGeneral/SpiLevelDelivered)"!][!//
[!/* Configuration of Jobs */!][!//
[!VAR "FoundJobCnt" = "0"!][!//
[!LOOP "node:order(SpiDriver/SpiJob/*, './SpiJobId')"!][!//
    [!VAR "SpiHwUnitID" ="substring-after(node:value(node:ref(node:ref(SpiDeviceAssignment)/SpiHwUnitRef)/SpiHWUnitMapping),'Spi_')"!][!//
    [!CALL "CG_FindSpiJobMappedCoreId", "SpiJobName"="node:name(.)"!][!//
    [!IF "$SpiJobMappedCoreId = $CoreIndex"!][!//
        [!VAR "FoundJobCnt" = "$FoundJobCnt + 1"!][!//
        [!INDENT "4"!][!//
        {
            [!INDENT "8"!][!//
            /* Spi Job ID: [!"node:name(.)"!] */
            (Spi_JobType)[!"num:i(SpiJobId)"!]U,
            /* SPI hardware number: Spi[!"$SpiHwUnitID"!] */
            (Spi_HWUnitType)[!"$SpiHwUnitID"!]U,
            /* Configure whether to release the chip select after each frame of data */
            [!IF "not(node:value(node:ref(node:ref(./SpiDeviceAssignment)/SpiHwUnitRef)/SpiEnableDMA) = 'true' and
                        (node:value(node:ref(./SpiDeviceAssignment)/SpiEnableCs) = 'true' and
                        node:exists(node:ref(./SpiDeviceAssignment)/SpiCsSelection) and
                        node:value(node:ref(./SpiDeviceAssignment)/SpiCsSelection) = 'CS_VIA_GPIO')) and
                  ./SpiReleaseCSEachData = 'true'"!]TRUE,[!ELSE!]FALSE,[!ENDIF!]
            /* External device ID configured by the job, [!"node:name(node:ref(./SpiDeviceAssignment))"!]" */
            (Spi_ExternalDeviceType)[!"num:i(node:value(node:ref(./SpiDeviceAssignment)/SpiExternalDeviceId))"!]U,
            /* [!"name(.)"!] total channel counts */
            (Spi_ChannelType)[!"num:i(count(SpiChannelList/*))"!]U,
            /* List of Channels */
            &[!"name(.)"!]_ChannelAssignment_PB[0],
            /* End Notification */
            [!IF "node:exists(SpiJobEndNotification) = 'true' and node:value(../../../SpiGeneral/SpiLevelDelivered) != 0"!][!//
                &[!"node:value(SpiJobEndNotification)"!],
            [!ELSE!][!//
                NULL_PTR,
            [!ENDIF!][!//
            /* Job Priority */
            [!"SpiJobPriority"!]U,
            /* Implementation specific field referencing the channel internal state. */
            &Spi_JobStateCore[!"$CoreIndex"!][[!"num:i($FoundJobCnt - 1)"!]]
            [!ENDINDENT!][!//
        }[!IF "num:i($FoundJobCnt) < $SpiJobNumCorex"!],[!ENDIF!]
        [!ENDINDENT!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************
  MACRO: CG_GenerateSeqConfig
  Generate Sequence configuration
*****************************************************************************/!]
[!MACRO "CG_GenerateSeqConfig"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!VAR "FoundSeqCnt" = "0"!][!//
[!LOOP "node:order(SpiDriver/SpiSequence/*, './SpiSequenceId')"!][!//
    [!CALL "CG_FindSpiSequenceMappedCoreId", "SpiSequenceName"="node:name(.)"!][!//
    [!IF "$SpiSequenceMappedCoreId = $CoreIndex"!][!//
        [!VAR "FoundSeqCnt" = "$FoundSeqCnt + 1"!][!//
        [!INDENT "4"!][!//
        {
            [!INDENT "8"!][!//
            /* SPI Sequence ID: [!"node:name(.)"!] */
            (Spi_SequenceType)[!"SpiSequenceId"!]U,
            /*SWS_Spi_00126:
                [!WS "3"!]When the SPI Handler/Driver is configured allowing interruptible Sequences, all Sequences
                [!WS "3"!]declared shall have their dedicated parameter SpiInterruptibleSequence (see SWS_Spi_00064
                [!WS "3"!]&amp; SPI106) to identify whether the Sequence can be suspended during transmission.
            */
            [!IF "../../../SpiGeneral/SpiInterruptibleSeqAllowed = 'true' and ./SpiInterruptibleSequence = 'true' and ../../../SpiGeneral/SpiLevelDelivered != num:i(0)"!][!//
            /* Sequence can be Interruptible */
                TRUE,
            [!ELSE!][!//
            /* Sequence cann't be Interruptible */
                FALSE,
            [!ENDIF!][!//
            /* Number of jobs in the sequence. */
            (Spi_JobType)[!"num:i(count(./SpiJobAssignment/*))"!]U,
            /* List of Jobs */
            &[!"name(.)"!]_JobAssignment_PB[0],
            [!IF "(../../../SpiGeneral/SpiLevelDelivered = '0' or ../../../SpiGeneral/SpiLevelDelivered = '2' ) and node:value(../../../SpiGeneral/SpiSupportConcurrentSyncTransmit) = 'true'"!][!//
                [!VAR "SeqUsedHwUnit" = "num:i(0)"!][!//
                [!FOR "UseHwUnitCnt" = "1" TO "num:i(count(./SpiJobAssignment/*))"!][!//
                    [!VAR "SpiHwUnitID" = "num:i(substring-after(node:value(node:ref(node:ref(node:ref(./SpiJobAssignment/*[num:i($UseHwUnitCnt)])/SpiDeviceAssignment)/SpiHwUnitRef)/SpiHWUnitMapping),'Spi_'))"!][!//
                    [!VAR "SeqUsedHwUnit" = "bit:or($SeqUsedHwUnit,bit:shl(1,$SpiHwUnitID))"!][!//
                [!ENDFOR!][!//
                /* bitx = 1 means Spix is occupy in current Sequence */
                (uint16)[!"num:inttohex($SeqUsedHwUnit,4)"!]U,
            [!ELSE!][!//
                /* Not supported, concurrent calls to Spi_SyncTransmit() between different sequences */
                (uint16)0xFFFFU,
            [!ENDIF!][!//
            /* End Notification */
            [!IF "node:exists(SpiSeqEndNotification) = 'true' and node:value(../../../SpiGeneral/SpiLevelDelivered) != 0"!][!//
                &[!"node:value(SpiSeqEndNotification)"!]
            [!ELSE!][!//
                NULL_PTR
            [!ENDIF!][!//
            [!ENDINDENT!][!//
        }[!IF "$FoundSeqCnt < $SpiSeqNumCorex"!],[!ENDIF!]
        [!ENDINDENT!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GenerateSequencelToCoreMap
  Generate Spi Sequencel To Corex Map
*****************************************************************************/!]
[!MACRO "CG_GenerateSequencelToCoreMap"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!VAR "SpiSequencelToCoreMap" = "''"!][!//
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "SpiSequencelToCoreMap" = "concat($SpiSequencelToCoreMap, $CoreIndex, ':255 ')"!][!//
[!ENDFOR!][!//
[!LOOP "node:order(SpiDriver/SpiSequence/*, './SpiSequenceId')"!][!//
    [!CALL "CG_FindSpiSequenceMappedCoreId", "SpiSequenceName"="node:name(.)"!][!//
    [!VAR "SequencelIndex" = "substring-after(text:split($SpiSequencelToCoreMap)[num:i($SpiSequenceMappedCoreId + 1)], ':')"!][!/* CoreId:Num--->1:2 */!][!//
    [!IF "num:i($SequencelIndex) = num:i(255)"!][!//
        [!VAR "SequencelIndex" = "num:i(0)"!][!//
    [!ELSE!][!//
        [!VAR "SequencelIndex" = "num:i(num:i($SequencelIndex) + 1)"!][!//
    [!ENDIF!][!//
    [!CALL "Spi_ChangeStrMember", "Object"="$SpiSequencelToCoreMap", "Index" = "$SpiSequenceMappedCoreId", "Value" = "$SequencelIndex"!][!//
    [!VAR "SpiSequencelToCoreMap" = "$ReturnObject"!][!//
    [!INDENT "4"!][!//
    [!IF "num:i($SequencelIndex) = num:i(255)"!][!//
        /* Warning: [!"node:name(.)"!] not assigned */
        0xFFU[!//
    [!ELSE!][!//
        /* [!"node:name(.)"!] configuration information is assigned to index[!"num:i($SequencelIndex)"!] of Core[!"$SpiSequenceMappedCoreId"!] */
        [!"num:i($SequencelIndex)"!]U[!//
    [!ENDIF!][!//
    [!IF "node:value(./SpiSequenceId) < num:i(count(../../SpiSequence/*) - 1)"!],[!ENDIF!]
    [!ENDINDENT!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GenerateJobToCoreMap
  Generate Spi Job To Corex Map
*****************************************************************************/!]
[!MACRO "CG_GenerateJobToCoreMap"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!VAR "SpiJobToCorexMap" = "''"!][!//
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "SpiJobToCorexMap" = "concat($SpiJobToCorexMap, $CoreIndex, ':255 ')"!][!//
[!ENDFOR!][!//
[!LOOP "node:order(SpiDriver/SpiJob/*, './SpiJobId')"!][!//
    [!CALL "CG_FindSpiJobMappedCoreId", "SpiJobName"="node:name(.)"!][!//
    [!VAR "JobIndex" = "substring-after(text:split($SpiJobToCorexMap)[num:i($SpiJobMappedCoreId + 1)], ':')"!][!/* CoreId:Num--->1:2 */!][!//
    [!IF "num:i($JobIndex) = num:i(255)"!][!//
        [!VAR "JobIndex" = "num:i(0)"!][!//
    [!ELSE!][!//
        [!VAR "JobIndex" = "num:i(num:i($JobIndex) + 1)"!][!//
    [!ENDIF!][!//
    [!CALL "Spi_ChangeStrMember", "Object"="$SpiJobToCorexMap", "Index" = "$SpiJobMappedCoreId", "Value" = "$JobIndex"!][!//
    [!VAR "SpiJobToCorexMap" = "$ReturnObject"!][!//
    [!INDENT "4"!][!//
    [!IF "num:i($JobIndex) = num:i(255)"!][!//
        /* Warning: [!"node:name(.)"!] not assigned */
        0xFFU[!//
    [!ELSE!][!//
        /* [!"node:name(.)"!] configuration information is assigned to index[!"num:i($JobIndex)"!] of Core[!"$SpiJobMappedCoreId"!] */
        [!"num:i($JobIndex)"!]U[!//
    [!ENDIF!][!//
    [!IF "node:value(./SpiJobId) < num:i(count(../../SpiJob/*) - 1)"!],[!ENDIF!]
    [!ENDINDENT!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GenerateChannelToCoreMap
  Generate Spi Channel To Corex Map
*****************************************************************************/!]
[!MACRO "CG_GenerateChannelToCoreMap"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!VAR "SpiChannelToCorexMap" = "''"!][!//
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "SpiChannelToCorexMap" = "concat($SpiChannelToCorexMap, $CoreIndex, ':255 ')"!][!//
[!ENDFOR!][!//
[!LOOP "node:order(SpiDriver/SpiChannel/*, './SpiChannelId')"!][!//
    [!CALL "CG_FindSpiChannelMappedCoreId", "SpiChannelName"="node:name(.)"!][!//
    [!VAR "ChannelIndex" = "substring-after(text:split($SpiChannelToCorexMap)[num:i($SpiChannelMappedCoreId + 1)], ':')"!][!/* CoreId:Num--->1:2 */!][!//
    [!IF "num:i($ChannelIndex) = num:i(255)"!][!//
        [!VAR "ChannelIndex" = "num:i(0)"!][!//
    [!ELSE!][!//
        [!VAR "ChannelIndex" = "num:i($ChannelIndex + 1)"!][!//
    [!ENDIF!][!//
    [!CALL "Spi_ChangeStrMember", "Object"="$SpiChannelToCorexMap", "Index" = "$SpiChannelMappedCoreId", "Value" = "$ChannelIndex"!][!//
    [!VAR "SpiChannelToCorexMap" = "$ReturnObject"!][!//
    [!INDENT "4"!][!//
    [!IF "num:i($ChannelIndex) = num:i(255)"!][!//
        /* Warning: [!"node:name(.)"!] not assigned */
        0xFFU[!//
    [!ELSE!][!//
        /* [!"node:name(.)"!] configuration information is assigned to index[!"num:i($ChannelIndex)"!] of Core[!"$SpiChannelMappedCoreId"!] */
        [!"num:i($ChannelIndex)"!]U[!//
    [!ENDIF!][!//
    [!IF "node:value(./SpiChannelId) < num:i(count(../../SpiChannel/*) - 1)"!],[!ENDIF!]
    [!ENDINDENT!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GenerateExternalDeviceToCoreMap
  Generate Spi External Device To Corex Map
*****************************************************************************/!]
[!MACRO "CG_GenerateExternalDeviceToCoreMap"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!VAR "SpiExternalDeviceToCorexMap" = "''"!][!//
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "SpiExternalDeviceToCorexMap" = "concat($SpiExternalDeviceToCorexMap, $CoreIndex, ':255 ')"!][!//
[!ENDFOR!][!//
[!LOOP "node:order(SpiDriver/SpiExternalDevice/*, './SpiExternalDeviceId')"!][!//
    [!CALL "CG_FindSpiExternalDeviceMappedCoreId", "SpiExternalDeviceName"="node:name(.)"!][!//
    [!VAR "ExternalDeviceIndex" = "substring-after(text:split($SpiExternalDeviceToCorexMap)[num:i($SpiExternalDeviceMappedCoreId + 1)], ':')"!][!/* CoreId:Num--->1:2 */!][!//
    [!IF "num:i($ExternalDeviceIndex) = num:i(255)"!][!//
        [!VAR "ExternalDeviceIndex" = "num:i(0)"!][!//
    [!ELSE!][!//
        [!VAR "ExternalDeviceIndex" = "num:i(num:i($ExternalDeviceIndex) + 1)"!][!//
    [!ENDIF!][!//
    [!CALL "Spi_ChangeStrMember", "Object"="$SpiExternalDeviceToCorexMap", "Index" = "$SpiExternalDeviceMappedCoreId", "Value" = "$ExternalDeviceIndex"!][!//
    [!VAR "SpiExternalDeviceToCorexMap" = "$ReturnObject"!][!//
    [!INDENT "4"!][!//
    [!IF "num:i($ExternalDeviceIndex) = num:i(255)"!][!//
        /* Warning: [!"node:name(.)"!] not assigned */
        0xFFU[!//
    [!ELSE!][!//
        [!VAR "SpiHwUnitID" ="substring-after(node:value(node:ref(./SpiHwUnitRef)/SpiHWUnitMapping),'Spi_')"!][!//
        /* [!"node:name(.)"!] configuration information is assigned to index[!"num:i($ExternalDeviceIndex)"!] of Core[!"$SpiExternalDeviceMappedCoreId"!] */
        /* [!"node:name(.)"!] is allocated to SPI[!"num:i($SpiHwUnitID)"!] */
        [!"num:i($ExternalDeviceIndex)"!]U[!//
    [!ENDIF!][!//
    [!IF "node:value(./SpiExternalDeviceId) < num:i(count(../../SpiExternalDevice/*) - 1)"!],[!ENDIF!]
    [!ENDINDENT!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GenerateHwUnitToCoreMap
  Generate Spi HwUnit To Corex Map
*****************************************************************************/!]
[!MACRO "CG_GenerateHwUnitToCoreMap"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!VAR "SpiHwUnitToCoreMap" = "''"!][!//
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "SpiHwUnitToCoreMap" = "concat($SpiHwUnitToCoreMap, $CoreIndex, ':255 ')"!][!//
[!ENDFOR!][!//
[!FOR "SpiHwUnitIndex" = "0" TO "num:i(num:i(ecu:get('Spi.MaxHwUnit')) - 1)"!][!//
    [!VAR "HwUnitIndex" = "num:i(255)"!][!//
    [!LOOP "node:order(SpiDriver/SpiHwUnitConfig/*, './SpiHWUnitMapping')"!][!//
        [!IF "text:split(./SpiHWUnitMapping, 'Spi_')[1] = $SpiHwUnitIndex"!][!//
            [!CALL "CG_FindSpiHwUnitMappedCoreId", "SpiHwUnitName"="node:name(.)"!][!//
            [!VAR "HwUnitIndex" = "substring-after(text:split($SpiHwUnitToCoreMap)[num:i($SpiHwUnitMappedCoreId + 1)], ':')"!][!/* CoreId:Num--->1:2 */!][!//
            [!IF "num:i($HwUnitIndex) = num:i(255)"!][!//
                [!VAR "HwUnitIndex" = "num:i(0)"!][!//
            [!ELSE!][!//
                [!VAR "HwUnitIndex" = "num:i(num:i($HwUnitIndex) + 1)"!][!//
            [!ENDIF!][!//
            [!CALL "Spi_ChangeStrMember", "Object"="$SpiHwUnitToCoreMap", "Index" = "$SpiHwUnitMappedCoreId", "Value" = "$HwUnitIndex"!][!//
            [!VAR "SpiHwUnitToCoreMap" = "$ReturnObject"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!INDENT "4"!][!//
    [!IF "num:i($HwUnitIndex) = num:i(255)"!][!//
        /* Spi[!"$SpiHwUnitIndex"!] not assigned */
        0xFFU[!//
    [!ELSE!][!//
        /* Spi[!"$SpiHwUnitIndex"!] configuration information is assigned to index[!"num:i($HwUnitIndex)"!] of Core[!"$SpiHwUnitMappedCoreId"!] */
        [!"num:i($HwUnitIndex)"!]U[!//
    [!ENDIF!][!//
    [!IF "num:i($SpiHwUnitIndex) != num:i(ecu:get('Spi.MaxHwUnit') - 1)"!],[!ENDIF!]
    [!ENDINDENT!][!//
[!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GenerateHwUnittoDmaChMap
  Generate DMA Channel to Spi HwUnit Map
*****************************************************************************/!]
[!MACRO "CG_GenerateHwUnittoDmaChMap"!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
[!VAR "HwUnitToDmaMap" = "''"!][!//
[!VAR "MaxDMAChannel" = "0"!][!//
[!VAR "RXDMAChannelID" = "0"!][!//
[!VAR "TXDMAChannelID" = "0"!][!//
[!LOOP "node:order(SpiDriver/SpiHwUnitConfig/*, './SpiHWUnitMapping')"!][!//
    [!IF "./SpiEnableDMA = 'true'"!][!//
        [!VAR "TXDMAChannelID" = "node:ref(./SpiTxDmaChannelRef)/DmaChannelId"!][!//
        [!VAR "RXDMAChannelID" = "node:ref(./SpiRxDmaChannelRef)/DmaChannelId"!][!//
        [!/* HwUnitToDmaMap = Spi_x:TxNum-RxNum Spi_x:TxNum-RxNum*/!]
        [!VAR "HwUnitToDmaMap" = "concat($HwUnitToDmaMap, ./SpiHWUnitMapping, ':TX=', $TXDMAChannelID, ' ')"!][!//
        [!VAR "HwUnitToDmaMap" = "concat($HwUnitToDmaMap, ./SpiHWUnitMapping, ':RX=', $RXDMAChannelID, ' ')"!][!//
        [!IF "$MaxDMAChannel < $TXDMAChannelID"!][!//
            [!VAR "MaxDMAChannel" = "$TXDMAChannelID"!][!//
        [!ENDIF!][!//
        [!IF "$MaxDMAChannel < $RXDMAChannelID"!][!//
            [!VAR "MaxDMAChannel" = "$RXDMAChannelID"!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!CALL "CG_GenerateHwUnittoDmaChMap"!][!//
[!/*****************************************************************************
  MACRO: CG_GenerateDmaChtoHwUnitMap
  Generate DMA Channel to Spi HwUnit Map
*****************************************************************************/!]
[!MACRO "CG_GenerateDmaChtoHwUnitMap"!][!//
[!//
[!CODE!][!//
[!INDENT "4"!][!//
[!FOR "DmaChannelIndex" = "0" TO "num:i($MaxDMAChannel)"!][!//
    [!IF "contains($HwUnitToDmaMap, concat('=', $DmaChannelIndex, ' '))"!][!//
        [!VAR "HwUnitString" = "text:split(substring-before($HwUnitToDmaMap, concat('=', $DmaChannelIndex, ' ')), ' ')[last()]"!][!//
        [!VAR "SpiHwUnit" = "substring-after(substring-before($HwUnitString, ':'), '_')"!][!//
        [!VAR "Direction" = "substring-after($HwUnitString, ':')"!][!//
        /* DMA Channel[!"$DmaChannelIndex"!] is assigned to Spi[!"$SpiHwUnit"!] [!"$Direction"!] Channel */
        [!"$SpiHwUnit"!]U[!//
    [!ELSE!][!//
        /* DMA Channel[!"$DmaChannelIndex"!] isn't assigned to Spi */
        0xFFU[!//
    [!ENDIF!][!//
    [!IF "num:i($DmaChannelIndex) != num:i($MaxDMAChannel)"!],[!ENDIF!]
[!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
MACRO: CG_AutoCalcDelayParams
Macro to Calculate the baudrate and delay params
******************************************************************************/!]
[!MACRO "CG_AutoCalcDelayParams", "ExternalDevice" = ""!][!//
[!//
[!NOCODE!][!//
[!SELECT "as:modconf('Spi')[1]/SpiDriver/SpiExternalDevice/*[node:name(.) = $ExternalDevice]"!]
    [!/******** Delay Calculation **********/!]
    [!VAR "SpiDelayIdlePre"="num:i(1)"!]
    [!VAR "SpiDelayIdleUnits"="num:i(1)"!]
    [!VAR "SpiDelayLeadPre"="num:i(1)"!]
    [!VAR "SpiDelayLeadUnits"="num:i(1)"!]
    [!VAR "SpiDelayTrailPre"="num:i(1)"!]
    [!VAR "SpiDelayTrailUnits"="num:i(1)"!]
    [!IF "node:value(./SpiAutoCalcDelayParams) = 'true'"!]
        [!VAR "SpiEbIdleTime"="./SpiIdleTime "!]
        [!VAR "SpiEbLeadTime"="./SpiTimeClk2Cs"!]
        [!VAR "SpiEbTrailTime"="./SpiTrailingTime "!]
        [!/* Idle Delay Params */!]
        [!VAR "SpiDelayParamIdle"="num:i(0)"!]
        [!VAR "SpiDelayParamIdleUnits"="num:i(0)"!]
        [!FOR "SpiDelayParamIdleUnits"="1" TO "9"!]
            [!IF "(round($SpiEbIdleTime * $SpiSystemClockFreq)) = (1 * ($SpiDelayParamIdleUnits))"!]
                [!VAR "SpiDelayParamIdle"="num:i(0)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbIdleTime * $SpiSystemClockFreq)) = (4 * ($SpiDelayParamIdleUnits))"!]
                [!VAR "SpiDelayParamIdle"="num:i(1)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbIdleTime * $SpiSystemClockFreq)) = (16 * ($SpiDelayParamIdleUnits))"!]
                [!VAR "SpiDelayParamIdle"="num:i(2)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbIdleTime * $SpiSystemClockFreq)) = (64 * ($SpiDelayParamIdleUnits))"!]
                [!VAR "SpiDelayParamIdle"="num:i(3)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbIdleTime * $SpiSystemClockFreq)) = (256 * ($SpiDelayParamIdleUnits))"!]
                [!VAR "SpiDelayParamIdle"="num:i(4)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbIdleTime * $SpiSystemClockFreq)) = (1024 * ($SpiDelayParamIdleUnits))"!]
                [!VAR "SpiDelayParamIdle"="num:i(5)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbIdleTime * $SpiSystemClockFreq)) = (4096 * ($SpiDelayParamIdleUnits))"!]
                [!VAR "SpiDelayParamIdle"="num:i(6)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbIdleTime * $SpiSystemClockFreq)) = (16384 * ($SpiDelayParamIdleUnits))"!]
                [!VAR "SpiDelayParamIdle"="num:i(7)"!]
                [!BREAK!]
            [!ENDIF!]
        [!ENDFOR!]
        [!IF "$SpiDelayParamIdleUnits < num:i(9)"!]
            [!VAR "SpiDelayParamIdleUnits"="num:i(($SpiDelayParamIdleUnits) -1)"!]
        [!ELSE!]
            [!ERROR!]
                [083-00-26-ERROR]: Autocalculation for the spcified Idle Delay(SpiIdleTime = [!"$SpiEbIdleTime"!]s) could not be done for the given frequence(SpiModuleClock = [!"$SpiSystemClockFreq"!]Hz)
            [!ENDERROR!]
        [!ENDIF!][!//
        [!/* Lead Delay Params */!]
        [!VAR "SpiDelayParamLead"="num:i(0)"!]
        [!VAR "SpiDelayParamLeadUnits"="num:i(0)"!]
        [!FOR "SpiDelayParamLeadUnits"="1" TO "9"!]
            [!IF "(round($SpiEbLeadTime * $SpiSystemClockFreq)) = (1 * ($SpiDelayParamLeadUnits))"!]
                [!VAR "SpiDelayParamLead"="num:i(0)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbLeadTime * $SpiSystemClockFreq)) = (4 * ($SpiDelayParamLeadUnits))"!]
                [!VAR "SpiDelayParamLead"="num:i(1)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbLeadTime * $SpiSystemClockFreq)) = (16 * ($SpiDelayParamLeadUnits))"!]
                [!VAR "SpiDelayParamLead"="num:i(2)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbLeadTime * $SpiSystemClockFreq)) = (64 * ($SpiDelayParamLeadUnits))"!]
                [!VAR "SpiDelayParamLead"="num:i(3)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbLeadTime * $SpiSystemClockFreq)) = (256 * ($SpiDelayParamLeadUnits))"!]
                [!VAR "SpiDelayParamLead"="num:i(4)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbLeadTime * $SpiSystemClockFreq)) = (1024 * ($SpiDelayParamLeadUnits))"!]
                [!VAR "SpiDelayParamLead"="num:i(5)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbLeadTime * $SpiSystemClockFreq)) = (4096 * ($SpiDelayParamLeadUnits))"!]
                [!VAR "SpiDelayParamLead"="num:i(6)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbLeadTime * $SpiSystemClockFreq)) = (16384 * ($SpiDelayParamLeadUnits))"!]
                [!VAR "SpiDelayParamLead"="num:i(7)"!]
                [!BREAK!]
            [!ENDIF!]
        [!ENDFOR!]
        [!IF "$SpiDelayParamLeadUnits < num:i(9)"!]
            [!VAR "SpiDelayParamLeadUnits"="num:i(($SpiDelayParamLeadUnits) -1)"!]
        [!ELSE!]
            [!ERROR!]
                [083-00-27-ERROR]: Autocalculation for the spcified Lead Delay(SpiTimeClk2Cs = [!"$SpiEbLeadTime"!]s) could not be done for the given frequence(SpiModuleClock = [!"$SpiSystemClockFreq"!]Hz)
            [!ENDERROR!][!//
        [!ENDIF!][!//
        [!/* Trail Delay Params */!][!//
        [!VAR "SpiDelayParamTrail"="num:i(0)"!]
        [!VAR "SpiDelayParamTrailUnits"="num:i(0)"!]
        [!FOR "SpiDelayParamTrailUnits"="1" TO "9"!]
            [!IF "(round($SpiEbTrailTime * $SpiSystemClockFreq)) = (1 * ($SpiDelayParamTrailUnits))"!]
                [!VAR "SpiDelayParamTrail"="num:i(0)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbTrailTime * $SpiSystemClockFreq)) = (4 * ($SpiDelayParamTrailUnits))"!]
                [!VAR "SpiDelayParamTrail"="num:i(1)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbTrailTime * $SpiSystemClockFreq)) = (16 * ($SpiDelayParamTrailUnits))"!]
                [!VAR "SpiDelayParamTrail"="num:i(2)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbTrailTime * $SpiSystemClockFreq)) = (64 * ($SpiDelayParamTrailUnits))"!]
                [!VAR "SpiDelayParamTrail"="num:i(3)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbTrailTime * $SpiSystemClockFreq)) = (256 * ($SpiDelayParamTrailUnits))"!]
                [!VAR "SpiDelayParamTrail"="num:i(4)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbTrailTime * $SpiSystemClockFreq)) = (1024 * ($SpiDelayParamTrailUnits))"!]
                [!VAR "SpiDelayParamTrail"="num:i(5)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbTrailTime * $SpiSystemClockFreq)) = (4096 * ($SpiDelayParamTrailUnits))"!]
                [!VAR "SpiDelayParamTrail"="num:i(6)"!]
                [!BREAK!]
            [!ENDIF!]
            [!IF "(round($SpiEbTrailTime * $SpiSystemClockFreq)) = (16384 * ($SpiDelayParamTrailUnits))"!]
                [!VAR "SpiDelayParamTrail"="num:i(7)"!]
                [!BREAK!]
            [!ENDIF!]
        [!ENDFOR!]
        [!IF "$SpiDelayParamTrailUnits < num:i(9)"!]
            [!VAR "SpiDelayParamTrailUnits"="num:i(($SpiDelayParamTrailUnits) -1)"!]
        [!ELSE!]
            [!ERROR!]
                [083-00-28-ERROR]: Autocalculation for the spcified Trail Delay(SpiTrailingTime = [!"$SpiEbTrailTime"!]s) could not be done for the given frequence(SpiModuleClock = [!"$SpiSystemClockFreq"!]Hz)
            [!ENDERROR!]
        [!ENDIF!][!//
    [!ELSE!][!//
        [!VAR "SpiDelayParamIdle"="node:value(./SpiDelayParams/*[1]/SpiParamIdle)"!]
        [!VAR "SpiDelayParamIdleUnits"="node:value(./SpiDelayParams/*[1]/SpiParamIdleUnit)"!]
        [!VAR "SpiDelayParamLead"="node:value(./SpiDelayParams/*[1]/SpiParamLead)"!]
        [!VAR "SpiDelayParamLeadUnits"="node:value(./SpiDelayParams/*[1]/SpiParamLeadUnit)"!]
        [!VAR "SpiDelayParamTrail"="node:value(./SpiDelayParams/*[1]/SpiParamTrail)"!]
        [!VAR "SpiDelayParamTrailUnits"="node:value(./SpiDelayParams/*[1]/SpiParamTrailUnit)"!]
        [!VAR "SpiEbIdleTime"="(bit:shl(1,$SpiDelayIdlePre*2)*($SpiDelayIdleUnits + 1)) div $SpiSystemClockFreq"!]
        [!VAR "SpiEbLeadTime"="(bit:shl(1,$SpiDelayLeadPre*2)*($SpiDelayLeadUnits + 1)) div $SpiSystemClockFreq"!]
        [!VAR "SpiEbTrailTime"="(bit:shl(1,$SpiDelayTrailPre*2)*($SpiDelayTrailUnits + 1)) div $SpiSystemClockFreq"!]
    [!ENDIF!][!//
[!ENDSELECT!]
[!ENDNOCODE!][!//
[!ENDMACRO!]

[!/*****************************************************************************
  MACRO: CG_GeneHwUnitMap
  Generate Spi available Espi hardware unit mapping table.
*****************************************************************************/!]
[!MACRO "CG_GeneHwUnitMap"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!FOR "HwUnitIndex" = "0" TO "num:i(ecu:get('Spi.MaxHwUnit') - 1)"!][!//
    [!INDENT "4"!][!//
        /* #Violation: Spi_PBcfg_c_REF_3 */
        ESPI[!"$HwUnitIndex"!][!IF "$HwUnitIndex != num:i(ecu:get('Spi.MaxHwUnit') - 1)"!],[!ELSE!][!WS!][!ENDIF!][!WS "8"!]/* Espi[!"$HwUnitIndex"!] is available*/
    [!ENDINDENT!][!//
    [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!ENDIF!]
[!ENDNOCODE!][!//
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
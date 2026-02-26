[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Lin.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : ASI
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
*   History:
*   2023-08-14 by YL
*     1. Original version 0.1
*
***************************************************************************************************/
[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!/* avoid multiple inclusion */!]
[!IF "not(var:defined('LIN_CFG_COMMON_M'))"!]
[!VAR "LIN_CFG_COMMON_M"="'true'"!]

[!NOCODE!][!//
[!IF "not(node:exists(as:modconf('Resource')[1]))"!][!//
[!ERROR!][!//
    082-00-01-ERROR: Resource module is not added to the project.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//

[!NOCODE!][!//
[!SELECT "as:modconf('Resource')[1]"!][!//
[!/* Find the master core */!][!//
[!VAR "Resource_MasterCore" = "node:value(ResourceCoreConfigSet/ResourceMasterCore)"!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//

[!/*****************************************************************************
  MACRO: CG_FindLinChannelMappedCoreId
  To find the CoreId according to the Lin channel
*****************************************************************************/!]
[!INDENT "0"!][!//
[!MACRO "CG_FindLinChannelMappedCoreId", "LinChannelId" = ""!][!//
    [!VAR "ModuleName" = "'LIN'"!][!//
    [!VAR "LinchannelMappedCoreId" = "num:i(0)"!][!//
    [!VAR "LinChannelMappedFlag" = "'false'"!][!//
    [!SELECT "as:modconf('Resource')[1]"!][!//
    [!LOOP "ResourceCoreConfigSet/ResourceCoreConfig/*"!][!//
        [!VAR "Resource_CoreId" = "./ResourceCoreId"!][!//
        [!VAR "Resource_CoreEnable" = "./ResourceCoreEnable"!][!//
        [!IF "$Resource_CoreEnable = 'true'"!][!//
            [!LOOP "ResourceAllocation/*"!][!//
                [!IF "./ResourceModule = $ModuleName"!][!//
                    [!IF "node:refvalid(./ResourceModuleRef) = 'true'"!][!//
                        [!VAR "index" = "num:i(count(text:split(./ResourceModuleRef, '/')))"!][!//
                        [!VAR "Resource_ModuleName" = "text:split(./ResourceModuleRef, '/')[num:i($index)]"!][!//
                        [!IF "$LinChannelId = $Resource_ModuleName"!][!//
                            [!VAR "LinchannelMappedCoreId" = "num:i(text:split($Resource_CoreId, 'CORE')[1])"!][!//
                            [!VAR "LinChannelMappedFlag" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!ERROR!][!//
                            082-00-02-ERROR: Invalid resource allocation done in [!"$Resource_CoreId"!] for [!"$ModuleName"!] module:[!"node:path(.)"!][!//
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!IF "$LinChannelMappedFlag = 'false'"!][!//
        [!/* If not allocated the Lin channel to any core will default allocate to core0 */!][!//
        [!VAR "LinchannelMappedCoreId" = "num:i(0)"!][!//
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/*****************************************************************************
  MACRO: CG_GeneLinWakeUpMacro
  Generate the macro definition for LIN channel name
*****************************************************************************/!]
[!MACRO "CG_GeneLinWakeUpMacro"!][!//
[!//
[!INDENT "0"!][!//
    [!VAR "LinWakeUpFlag" = "'false'"!][!//
    [!LOOP "LinGlobalConfig/LinChannel/*"!][!//
        [!IF "./LinChannelWakeupSupport = 'true'"!][!//
            [!VAR "LinWakeUpFlag" = "'true'"!][!//
            [!BREAK!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
#define LIN_WAKEUP_SUPPORT              [!WS "21"!][!IF "$LinWakeUpFlag = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
[!ENDINDENT!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GeneLinChannelIdMacro
  Generate the macro definition for LIN channel name
*****************************************************************************/!]
[!MACRO "CG_GeneLinChannelIdMacro"!][!//
[!//
[!INDENT "0"!][!//
    [!LOOP "LinGlobalConfig/LinChannel/*"!][!//
        [!CALL "CG_FindLinChannelMappedCoreId", "LinChannelId" = "node:name(.)"!][!//
        #ifndef LinConf_LinChannel_[!"node:name(.)"!]
        /* LIN Channel ID [!"./LinChannelId"!] -> [!"name(.)"!], mapped to [!"./LinHwUnit"!] in Core[!"$LinchannelMappedCoreId"!] */
        #define LinConf_LinChannel_[!"node:name(.)"!]                               ([!"num:i(node:value(./LinChannelId))"!]U)
        #define LIN_HWUNIT_CHANNEL[!"substring-after(./LinHwUnit,'ASI')"!]
        #endif
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GeneLinHwUnitConfig
  Generate LIN channel hardware config information
*****************************************************************************/!]
[!MACRO "CG_GeneLinHwUnitConfig", "CoreID" = ""!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!VAR "CorexLinNum" = "num:i(0)"!][!//
    [!VAR "TotalChannelNum" = "num:i(count(LinGlobalConfig/LinChannel/*))"!][!//
    [!FOR "ChannelIndex" = "0" TO "num:i($TotalChannelNum - 1)"!][!//
        [!/* Generated in ascending of Lin channels */!][!//
        [!LOOP "LinGlobalConfig/LinChannel/*"!][!//
            [!IF "LinChannelId = $ChannelIndex"!][!//
                [!CALL "CG_FindLinChannelMappedCoreId", "LinChannelId"="node:name(.)"!][!//
                [!IF "num:i($LinchannelMappedCoreId) = $CoreID"!][!//
                    [!VAR "CorexLinNum" = "$CorexLinNum + 1"!][!//
                    [!SELECT "as:modconf('Lin')[1]"!][!//
                    [!VAR "LinSpdClock" = "node:value(node:ref(LinClockSet/LinSysClockRef)/McuClockReferencePointFrequency)"!][!//
                    [!VAR "LinInterruptType" = "LinGeneral/LinInterruptEnable"!][!//
                    [!ENDSELECT!][!//
                    [!INDENT "4"!][!//
                    {
                        [!INDENT "8"!][!//
                            /* Master or Slave mode */
                            [!IF "node:value(LinNodeType) = 'MASTER'"!][!//
                                ASI_LIN_MODE_MASTER,
                            [!ELSE!][!//
                                ASI_LIN_MODE_SLAVE,
                            [!ENDIF!][!//
                            /* Frame break length */
                            ASI_[!"LinFrameBreakFieldLength"!],
                            [!VAR "BaudRateRegValue" = "num:f($LinSpdClock div LinChannelBaudRate)"!][!//
                            /* Baud-rate ratio: Clock[[!"$LinSpdClock"!]]/baud-rate[[!"LinChannelBaudRate"!]]/RegisterValue[[!"num:inttohex($BaudRateRegValue)"!]] */
                            /* Integer Baud rate = RegisterValue / 16 */
                            [!"num:i($BaudRateRegValue div 16)"!]U,
                            /* Fractional Baud rate = RegisterValue % 16 */
                            [!"num:i(num:f(num:f($BaudRateRegValue div 16) - num:i(num:f($BaudRateRegValue div 16))) * 16)"!]U,
                            /* Enable/disable Error/RX/AutoWakeup interrupt */
                            [!IF "$LinInterruptType = 'true'"!][!//
                                [!IF "node:value(LinNodeType) = 'MASTER'"!][!//
                                    (ASI_LIN_DATA_RX_COMPLETED_INT | ASI_LIN_WAKEUP_INT | ASI_LIN_ALL_ERROR_INTS),
                                [!ELSE!][!//
                                    (ASI_LIN_DATA_RX_COMPLETED_INT | ASI_LIN_WAKEUP_INT | ASI_LIN_ALL_ERROR_INTS | ASI_LIN_DATA_TX_COMPLETED_INT | ASI_LIN_HEADER_RX_INT),
                                [!ENDIF!][!//
                            [!ELSE!][!//
                                0x00U,
                            [!ENDIF!][!//
                            /* Frame header(Max:0x2F) or response Timeout Value(Max:0x0F) */
                            [!IF "node:value(LinNodeType) = 'MASTER'"!][!//
                                0xE,
                            [!ELSE!][!//
                                0x2F,
                            [!ENDIF!][!//
                            /* ID filter configuration, only for slave node */
                            NULL_PTR,
                            /* Enable auto wake-up */
                            TRUE,
                            /* Enable or disable master RX with DMA */
                            FALSE,
                            /* Enable/disable RX buffer lock mode */
                            FALSE
                        [!ENDINDENT!][!//
                    }[!IF "num:i($CorexLinNum) != num:i($LinTotalHWUnitNum)"!],[!ENDIF!]
                    [!ENDINDENT!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GeneLinChannelConfig
  Generate LIN Channel config information
*****************************************************************************/!]
[!MACRO "CG_GeneLinChannelConfig", "CoreID" = ""!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!VAR "CorexLinNum" = "num:i(0)"!][!//
    [!VAR "TotalChannelNum" = "num:i(count(LinGlobalConfig/LinChannel/*))"!][!//
    [!FOR "ChannelIndex" = "0" TO "num:i($TotalChannelNum - 1)"!][!//
        [!/* Generated in ascending of Lin channels */!][!//
        [!LOOP "LinGlobalConfig/LinChannel/*"!][!//
            [!IF "LinChannelId = $ChannelIndex"!][!//
                [!CALL "CG_FindLinChannelMappedCoreId", "LinChannelId"="node:name(.)"!][!//
                [!IF "num:i($LinchannelMappedCoreId) = $CoreID"!][!//
                    [!SELECT "as:modconf('Lin')[1]"!][!//
                    [!VAR "LinSpdClock" = "node:value(node:ref(LinClockSet/LinSysClockRef)/McuClockReferencePointFrequency)"!][!//
                    [!ENDSELECT!][!//
                    [!INDENT "4"!][!//
                    {
                        [!INDENT "8"!][!//
                        /* Lin Channel ID */
                        [!"LinChannelId"!]U,
                        /* ASI HwUnit([!"LinHwUnit"!]) of assigned to Lin channel */
                        [!"text:split(LinHwUnit, 'ASI')[1]"!]U,
                        /* Is wake-up supported by the LIN channel */
                        [!IF "node:value(LinChannelWakeupSupport) = 'true'"!][!//
                            TRUE,
                        [!ELSE!][!//
                            FALSE,
                        [!ENDIF!][!//
                        /* This parameter contains a reference to the Wake-up Source for this controller
                         * as defined in the ECU State Manager.*/
                        [!IF "node:value(LinChannelWakeupSupport) = 'false'"!][!//
                            [!IF "node:refexists(./LinChannelEcuMWakeupSource/*[1]) = 'true'"!][!//
                                /* [!"./LinChannelEcuMWakeupSource/*[1]"!]U, 
                                This parameter is not support*/
                                0U,
                            [!ELSE!][!//
                                0U,
                            [!ENDIF!][!//
                        [!ELSE!][!//
                            0U,
                        [!ENDIF!][!//
                        /* The configuration information structure of the hardware unit([!"LinHwUnit"!]) corresponding to the Channel[!"LinChannelId"!] */
                        &Lin_HWUnitConfigSetCore[!"$CoreIndex"!][[!"num:i($CorexLinNum)"!]]
                        [!ENDINDENT!][!//
                        [!VAR "CorexLinNum" = "$CorexLinNum + 1"!][!//
                    }[!IF "num:i($CorexLinNum) != num:i($LinTotalHWUnitNum)"!],[!ENDIF!]
                    [!ENDINDENT!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GeneChannelToCoreMap
  Generate LIN channel hardware config information
*****************************************************************************/!]
[!MACRO "CG_GeneChannelToCoreMap"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!VAR "LC_LinChannelMappedCoreIdDict" = "''"!][!//
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "LC_LinChannelMappedCoreIdDict" = "concat($LC_LinChannelMappedCoreIdDict, $CoreIndex, ':255 ')"!][!//
[!ENDFOR!][!//
[!LOOP "node:order(LinGlobalConfig/LinChannel/*, './LinChannelId')"!][!//
    [!CALL "CG_FindLinChannelMappedCoreId", "LinChannelId" = "node:name(.)"!][!//
    [!VAR "ChannelIndex" = "substring-after(text:split($LC_LinChannelMappedCoreIdDict)[num:i($LinchannelMappedCoreId + 1)], ':')"!][!/* CoreId:Num--->1:2 */!][!//
    [!IF "num:i($ChannelIndex) = num:i(255)"!][!//
        [!VAR "ChannelIndex" = "num:i(0)"!][!//
    [!ELSE!][!//
        [!VAR "ChannelIndex" = "num:i(num:i($ChannelIndex) + 1)"!][!//
    [!ENDIF!][!//
    [!VAR "BeforeLinChannelToCorexMapText" = "substring-before($LC_LinChannelMappedCoreIdDict, concat($LinchannelMappedCoreId, ':'))"!][!//
    [!VAR "AfterLinChannelToCorexMapText" = "substring-after($LC_LinChannelMappedCoreIdDict, concat(LinchannelMappedCoreId, ':', string(substring-after(text:split($LC_LinChannelMappedCoreIdDict)[num:i($LinchannelMappedCoreId + 1)], ':'))))"!][!//
    [!VAR "LC_LinChannelMappedCoreIdDict" = "concat($BeforeLinChannelToCorexMapText, concat($LinchannelMappedCoreId , ':', num:i($ChannelIndex)), $AfterLinChannelToCorexMapText)"!][!//
    [!INDENT "4"!][!//
    [!IF "num:i($ChannelIndex) = num:i(255)"!][!//
        /* Warning: [!"node:name(.)"!] not assigned */
        0xFFU[!//
    [!ELSE!][!//
        /* [!"node:name(.)"!] configuration information is assigned to index[!"num:i($ChannelIndex)"!] of Core[!"$LinchannelMappedCoreId"!] */
        [!"num:i($ChannelIndex)"!]U[!//
    [!ENDIF!][!//
    [!IF "node:value(./LinChannelId) < num:i(count(../../LinChannel/*) - 1)"!],[!ENDIF!]
    [!ENDINDENT!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GeneHwUnitNumToLinChannel
  Generate LIN channel number mapping table corresponding to hardware
*****************************************************************************/!]
[!INDENT "0"!][!//
[!MACRO "CG_GeneHwUnitNumToLinChannel"!][!//
    [!FOR "HwUnitIndex" = "0" TO "num:i(ecu:get('Asi.MaxHwUnit') - 1)"!][!//
    [!VAR "HwUnitFoundFlg" = "0"!][!//
    [!INDENT "4"!][!//
        [!LOOP "LinGlobalConfig/LinChannel/*"!][!//
            [!IF "$HwUnitIndex = text:split(LinHwUnit, 'ASI')[1] "!][!//
                [!VAR "HwUnitFoundFlg" = "1"!][!//
                [!CALL "CG_FindLinChannelMappedCoreId", "LinChannelId" = "node:name(.)"!][!//
                /* ASI[!"$HwUnitIndex"!] assigned to LinChannel_[!"LinChannelId"!] in Core[!"$LinchannelMappedCoreId"!] */
                [!"LinChannelId"!]U[!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$HwUnitFoundFlg = 0"!][!//
            /* ASI[!"$HwUnitIndex"!] not assigned */
            0xFFU[!//
        [!ENDIF!][!//
        [!IF "$HwUnitIndex != num:i(ecu:get('Asi.MaxHwUnit') - 1)"!],[!ENDIF!]
    [!ENDINDENT!][!//
    [!ENDFOR!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/*****************************************************************************
  MACRO: CG_IncVauleInStringDictByKey
    Perform +1 processing on the member with index in StringDict
    StringDict: key-value pair's value who want to change
    Index : key
*****************************************************************************/!]
[!MACRO "CG_IncVauleInStringDictByKey", "StringDict" = "", "Key" = ""!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!/* 
        1st: split $StringDict using ' ' 
        2nd: get the value of $Key:$Vaule
        3rd: get the value of $Key:$Vaule by substring-after using ':'
    */!][!//
    [!VAR "Value" = "substring-after(text:split($StringDict)[num:i($Key + 1)], ':')"!][!//
    [!VAR "BeforeString" = "concat($Key, ':', $Value, ' ')"!][!/* CoreId:Num--->1:2 */!][!//
    [!VAR "AfterString"  = "concat($Key, ':', num:i($Value + 1), ' ')"!][!/* CoreId:Num--->1:3 */!][!//
    [!VAR "CG_IncVauleInStringDictByKey_ReturnObject" = "text:replace($StringDict, $BeforeString, $AfterString)"!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!MACRO "CG_GetVauleInStringDictByKey", "StringDict" = "", "Key" = ""!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "CG_GetVauleInStringDictByKey_Local_Value" = "num:i(substring-after(text:split($StringDict)[num:i($Key + 1)], ':'))"!][!//
    [!VAR "CG_GetVauleInStringDictByKey_ReturnObject" = "$CG_GetVauleInStringDictByKey_Local_Value"!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GetLinChannelNumbertoCoreIdDict
  Get LIN channel number to core id mapping table(which is a string Dict)
  e.g. '0:1 1:3' -- means Core0 has 1 LinChannel, Core1 has 3 LinChannels
*****************************************************************************/!]
[!MACRO "CG_GetLinChannelNumbertoCoreIdDict"!][!//
[!//
[!NOCODE!][!//
[!VAR "G_LinChannelMappedCoreIdDict" = "''"!][!//
[!/* Init global dict var, e.g. '0:0 1:0 2:0 3:0' */!][!//
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "G_LinChannelMappedCoreIdDict" = "concat($G_LinChannelMappedCoreIdDict, $CoreIndex, ':0 ')"!][!//
[!ENDFOR!][!//
[!/* Add number of LinChannel in specific Core into gloal number dict */!][!//
[!LOOP "LinGlobalConfig/LinChannel/*"!][!//
    [!CALL "CG_FindLinChannelMappedCoreId", "LinChannelId"="node:name(.)"!][!//
    /* Get current Lin channel belongs to core index */
    [!CALL "CG_IncVauleInStringDictByKey", "StringDict" = "$G_LinChannelMappedCoreIdDict", "Key" = "$LinchannelMappedCoreId"!][!//
    [!VAR "G_LinChannelMappedCoreIdDict" = "$CG_IncVauleInStringDictByKey_ReturnObject"!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//


[!NOCODE!][!//
[!/* Find the LinChannel number of corex */!][!//
[!CALL "CG_GetLinChannelNumbertoCoreIdDict"!][!//
[!ENDNOCODE!][!//

[!ENDIF!][!// avoid multiple inclusion ENDIF
[!ENDNOCODE!][!//


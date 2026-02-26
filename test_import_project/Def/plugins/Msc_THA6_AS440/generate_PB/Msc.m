/****************************************************************************************************
*   FileName              : Msc.m
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MSC
*
*   brief                 : This file contains many MACROS used by the Msc Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

[!INDENT "0"!][!//
/*******************************************************************************
** Name           : Msc_FindChannelMappedCoreId                               **
**                                                                            **
** Description    : This macro to get the channel mapping core                **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!/* To find the CoreId according to the GPT channel */!][!//
[!MACRO "Msc_FindChannelMappedCoreId", "MscChId" = ""!][!//
    [!VAR "ModuleName" = "'MSC'"!][!//
    [!VAR "MscChannelMappedCoreId" = "num:i(0)"!][!//
    [!VAR "MscChannelMappedFlag" = "'false'"!][!//
    [!SELECT "as:modconf('Resource')[1]"!][!//
    [!LOOP "ResourceCoreConfigSet/ResourceCoreConfig/*"!][!//
        [!VAR "Resource_CoreId" = "./ResourceCoreId"!][!//
        [!VAR "Resource_CoreEnable" = "./ResourceCoreEnable"!][!//
        [!IF "$Resource_CoreEnable = 'true'"!][!//
            [!LOOP "ResourceAllocation/*"!][!//
                [!IF "./ResourceModule = $ModuleName"!][!//
                    [!IF "node:refvalid(./ResourceModuleRef) = 'true'"!][!//
                        [!VAR "Resource_ModuleName" = "text:split(./ResourceModuleRef, '/')[last()]"!][!//
                        [!IF "$MscChId = $Resource_ModuleName"!][!//
                            [!VAR "MscChannelMappedCoreId" = "num:i(text:split($Resource_CoreId, 'CORE')[1])"!][!//
                            [!VAR "MscChannelMappedFlag" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!ERROR!][!//
                            255-04-00-ERROR: Invalid resource allocation done in [!"$Resource_CoreId"!] for [!"$ModuleName"!] module:[!"node:path(.)"!][!//
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!IF "$MscChannelMappedFlag = 'false'"!][!//
        [!/* If not allocated the GPT channel to any core will default allocate to core0 */!][!//
        [!VAR "MscChannelMappedCoreId" = "num:i(0)"!][!//
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Find which core used for MSC channel */!][!//
[!INDENT "0"!][!//
[!MACRO "Msc_FindTotalNumMscChannelMappedToCorex"!][!//
    [!VAR "MscChannelMappedCore0" = "0"!][!//
    [!VAR "MscChannelMappedCore1" = "0"!][!//
    [!VAR "MscChannelMappedCore2" = "0"!][!//
    [!VAR "MscChannelMappedCore3" = "0"!][!//
    [!VAR "MscChannelMappedCore4" = "0"!][!//
    [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigSet/MscModuleConfiguration/*, 'MscHWUnitMapping')"!][!//
        [!CALL "Msc_FindChannelMappedCoreId", "MscChId"="node:name(.)"!][!//
        [!IF "$MscChannelMappedCoreId = num:i(0)"!][!//
            [!VAR "MscChannelMappedCore0" = "$MscChannelMappedCore0 + 1"!][!//
        [!ELSEIF "$MscChannelMappedCoreId = num:i(1)"!][!//
            [!VAR "MscChannelMappedCore1" = "$MscChannelMappedCore1 + 1"!][!//
        [!ELSEIF "$MscChannelMappedCoreId = num:i(2)"!][!//
            [!VAR "MscChannelMappedCore2" = "$MscChannelMappedCore2 + 1"!][!//
        [!ELSEIF "$MscChannelMappedCoreId = num:i(3)"!][!//
            [!VAR "MscChannelMappedCore3" = "$MscChannelMappedCore3 + 1"!][!//
        [!ELSEIF "$MscChannelMappedCoreId = num:i(4)"!][!//
            [!VAR "MscChannelMappedCore4" = "$MscChannelMappedCore4 + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!CALL "Msc_FindTotalNumMscChannelMappedToCorex"!]

[!/*****************************************************************************
** Name             : Msc_DataSRConfig                                        **
**                                                                            **
** Description      : Macro to data source selection                          **
**                                                                            **
******************************************************************************/!]
[!MACRO "Msc_DataSRConfig", "BitNo" = "", "SourceSel"="", "SRConfig"="", "DataMask"="", "SRConfigExtension"="", "DataMaskExtension"=""!]
[!NOCODE!]
[!IF "$BitNo <= num:i(15)"!][!//
    [!IF "$SourceSel = 'SRC_DOWNSTREAMDATA'"!][!//
        [!VAR "DataMask" = "bit:or($DataMask,bit:shl(num:i(1),($BitNo)))"!][!//
    [!ELSEIF "$SourceSel= 'SRC_GTMSIGNAL'"!][!//
        [!VAR "SRConfig" = "bit:or($SRConfig,bit:shl(2,($BitNo * 2)))"!][!//
        [!VAR "DataMask" = "bit:bitclear($DataMask,num:i($BitNo))"!][!//
    [!ELSE!][!//
        [!VAR "SRConfig" = "bit:or($SRConfig,bit:shl(3,($BitNo * 2)))"!][!//
        [!VAR "DataMask" = "bit:bitclear($DataMask,num:i($BitNo))"!][!//
    [!ENDIF!][!//
[!ELSE!][!//
    [!VAR "NewBitNo" = "num:i($BitNo - num:i(16))"!][!//

    [!IF "$SourceSel = 'SRC_DOWNSTREAMDATA'"!][!//
        [!VAR "DataMaskExtension" = "bit:or($DataMaskExtension,bit:shl(1,($NewBitNo)))"!][!//
    [!ELSEIF "$SourceSel= 'SRC_GTMSIGNAL'"!][!//
        [!VAR "SRConfigExtension" = "bit:or($SRConfigExtension,bit:shl(2,($NewBitNo * 2)))"!][!//
        [!VAR "DataMaskExtension" = "bit:bitclear(num:i($DataMaskExtension),num:i($NewBitNo))"!][!//
    [!ELSE!][!//
        [!VAR "SRConfigExtension" = "bit:or($SRConfigExtension,bit:shl(3,($NewBitNo * 2)))"!][!//
        [!VAR "DataMaskExtension" = "bit:bitclear($DataMaskExtension,num:i($NewBitNo))"!][!//
    [!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!]
[!ENDMACRO!]

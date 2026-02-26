[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : I2c.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : I2C
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
***************************************************************************************************/
[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!/* avoid multiple inclusion */!]
[!IF "not(var:defined('I2C_CFG_COMMON_M'))"!]
[!VAR "I2C_CFG_COMMON_M"="'true'"!]

[!NOCODE!][!//
[!IF "not(node:exists(as:modconf('Resource')[1]))"!][!//
[!ERROR!][!//
    082-00-01-ERROR: Resource module is not added to the project.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//

[!/*****************************************************************************
  MACRO: CG_FindI2cChannelMappedCoreId
  To find the CoreId according to the I2c channel
*****************************************************************************/!]
[!INDENT "0"!][!//
[!MACRO "CG_FindI2cChannelMappedCoreId", "I2cChannelId" = ""!][!//
    [!VAR "ModuleName" = "'I2C'"!][!//
    [!VAR "I2cChannelMappedCoreId" = "num:i(0)"!][!//
    [!VAR "I2cChannelMappedFlag" = "'false'"!][!//
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
                        [!IF "$I2cChannelId = $Resource_ModuleName"!][!//
                            [!VAR "I2cChannelMappedCoreId" = "num:i(text:split($Resource_CoreId, 'CORE')[1])"!][!//
                            [!VAR "I2cChannelMappedFlag" = "'true'"!][!//
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
    [!IF "$I2cChannelMappedFlag = 'false'"!][!//
        [!/* If not allocated the I2c channel to any core will default allocate to core0 */!][!//
        [!VAR "I2cChannelMappedCoreId" = "num:i(0)"!][!//
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/*****************************************************************************
  MACRO: I2c_ChangeStrMember
    Object: StringList operation object, whose members are in the form of key-value pairs in the form of <key:KeyValue>
    Index : StringList member subscript index value
    Value : ''    : Perform +1 processing on the member with index in Object
            $Value: Use "$Value" to replace the indexed member in Object
*****************************************************************************/!]
[!MACRO "I2c_ChangeStrMember", "Object" = "", "Index" = "", "Value" = ""!][!//
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
  MACRO: CG_FindTotalNumI2cChannelMappedToCorex
  To find the CoreId according to the I2c channel
*****************************************************************************/!]
[!MACRO "CG_FindTotalNumI2cChannelMappedToCorex"!][!//
[!INDENT "0"!][!//
    [!VAR "I2cChannelTotalNumCorex" = "''"!][!//
    [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        [!VAR "I2cChannelTotalNumCorex" = "concat($I2cChannelTotalNumCorex, $CoreIndex, ':0 ')"!][!//
    [!ENDFOR!][!//
    [!LOOP "node:order(I2cGlobalConfig/I2cChannel/*, './I2cChannelId')"!][!//
        [!CALL "CG_FindI2cChannelMappedCoreId", "I2cChannelId"="node:name(.)"!][!//
        [!IF "$I2cChannelMappedCoreId != num:i(255)"!][!//
            [!CALL "I2c_ChangeStrMember", "Object"="$I2cChannelTotalNumCorex", "Index" = "$I2cChannelMappedCoreId", "Value" = "''"!][!//
            [!VAR "I2cChannelTotalNumCorex" = "$ReturnObject"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//

[!CALL "CG_FindTotalNumI2cChannelMappedToCorex"!]

[!/*****************************************************************************
  MACRO: CG_GeneI2cHwUnitConfig
  Generate I2c channel hardware config information
*****************************************************************************/!]
[!MACRO "CG_GeneI2cHwUnitConfig", "CoreID" = ""!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!VAR "FoundChannelCnt" = "num:i(0)"!][!//
    [!LOOP "node:order(I2cGlobalConfig/I2cChannel/*, './I2cChannelId')"!][!//
        [!CALL "CG_FindI2cChannelMappedCoreId", "I2cChannelId"="node:name(.)"!][!//
        [!IF "num:i($I2cChannelMappedCoreId) = $CoreID"!][!//
            [!VAR "FoundChannelCnt" = "num:i($FoundChannelCnt + 1)"!][!//
            [!INDENT "4"!][!//
            {
                [!INDENT "8"!][!//
                    /* FIFO mode */
                    TRUE,
                    /* RX-FIFO water mark */
                    4U,
                    /* TX-FIFO water mark */
                    4U,
                    /* FIFO AlignMode */
                    I2C_FIFO_ALIGNBYTE_1,
                    /* Bus Speed */
                    I2C_[!"I2cBusSpeed"!],
                    [!IF "I2cDutyCycle = 'RATIO_16_9'"!][!//
                        /* I2C fast mode Tlow/Thigh = 16/9 */
                        0x00000001U,
                    [!ELSE!][!//
                        /* I2C fast mode Tlow/Thigh = 2 */
                        0x00000000U,
                    [!ENDIF!][!//
                    /* Single transmition */
                    0U
                [!ENDINDENT!][!//
            }[!IF "num:i($FoundChannelCnt) < num:i($I2cChannelNumCorex)"!],[!ENDIF!]
            [!ENDINDENT!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GeneI2cChannelConfig
  Generate I2C Channel config information
*****************************************************************************/!]
[!MACRO "CG_GeneI2cChannelConfig", "CoreID" = ""!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!VAR "FoundChannelCnt" = "num:i(0)"!][!//
    [!LOOP "node:order(I2cGlobalConfig/I2cChannel/*, './I2cChannelId')"!][!//
        [!CALL "CG_FindI2cChannelMappedCoreId", "I2cChannelId"="node:name(.)"!][!//
        [!IF "num:i($I2cChannelMappedCoreId) = $CoreID"!][!//
            [!INDENT "4"!][!//
            {
                [!INDENT "8"!][!//
                /* The configuration information structure of the hardware unit([!"./I2cHwUnit"!]) corresponding to the Channel[!"./I2cChannelId"!] */
                &I2c_HWUnitConfigSetCore[!"$CoreIndex"!][[!"num:i($FoundChannelCnt)"!]],
                /* Pointer to the notification function */
                [!IF "./I2cNotification = 'true' and
                    node:exists(I2cPacketEndNotification) and
                    node:value(I2cPacketEndNotification) != 'NULL_PTR' and
                    node:value(I2cPacketEndNotification) != ''"!][!//
                    [!"I2cPacketEndNotification"!],
                [!ELSE!][!//
                    NULL_PTR,
                [!ENDIF!][!//
                /* I2C HwUnit([!"./I2cHwUnit"!]) of assigned to I2c channel */
                [!"text:split(./I2cHwUnit, 'I2C')[1]"!]U,
                /* I2C Channel ID */
                [!"I2cChannelId"!]U
                [!ENDINDENT!][!//
                [!VAR "FoundChannelCnt" = "num:i($FoundChannelCnt + 1)"!][!//
            }[!IF "num:i($FoundChannelCnt) != num:i($I2cChannelNumCorex)"!],[!ENDIF!]
            [!ENDINDENT!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GeneChannelToCoreMap
  Generate I2C channel hardware config information
*****************************************************************************/!]
[!MACRO "CG_GeneChannelToCoreMap"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!INDENT "4"!][!//
    [!VAR "I2cChannelMappedCorex" = "''"!][!//
    [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        [!VAR "I2cChannelMappedCorex" = "concat($I2cChannelMappedCorex, $CoreIndex, ':255 ')"!][!//
    [!ENDFOR!][!//
    [!VAR "I2cChannelTotalNum" = "count(I2cGlobalConfig/I2cChannel/*)"!][!//
    [!LOOP "node:order(I2cGlobalConfig/I2cChannel/*, './I2cChannelId')"!][!//
        [!CALL "CG_FindI2cChannelMappedCoreId", "I2cChannelId"="node:name(.)"!][!//
        [!VAR "I2cChannelIndex" = "substring-after(text:split($I2cChannelMappedCorex)[num:i($I2cChannelMappedCoreId + 1)], ':')"!][!/* CoreId:Num--->1:2 */!][!//
        [!IF "num:i($I2cChannelIndex) = num:i(255)"!][!//
            [!VAR "I2cChannelIndex" = "num:i(0)"!][!//
        [!ELSE!][!//
            [!VAR "I2cChannelIndex" = "num:i($I2cChannelIndex + 1)"!][!//
        [!ENDIF!][!//
        [!CALL "I2c_ChangeStrMember", "Object"="$I2cChannelMappedCorex", "Index" = "$I2cChannelMappedCoreId", "Value" = "$I2cChannelIndex"!][!//
        [!VAR "I2cChannelMappedCorex" = "$ReturnObject"!][!//
        /* I2cChannel_[!"./I2cChannelId"!] configuration information is assigned to index[!"num:i($I2cChannelIndex)"!] of Core[!"$I2cChannelMappedCoreId"!] */
        [!"num:i($I2cChannelIndex)"!]U[!IF "node:value(./I2cChannelId) < num:i($I2cChannelTotalNum - 1)"!],[!ENDIF!]
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GeneHwUnitNumToI2cChannel
  Generate I2C channel number mapping table corresponding to hardware
*****************************************************************************/!]
[!INDENT "0"!][!//
[!MACRO "CG_GeneHwUnitNumToI2cChannel"!][!//
    [!FOR "HwUnitIndex" = "0" TO "num:i(ecu:get('I2c.NumofAvailableI2c') - 1)"!][!//
    [!VAR "HwUnitFoundFlg" = "'false'"!][!//
    [!INDENT "4"!][!//
        [!LOOP "node:order(I2cGlobalConfig/I2cChannel/*, './I2cChannelId')"!][!//
            [!IF "$HwUnitIndex = text:split(I2cHwUnit, 'I2C')[1] "!][!//
                [!VAR "HwUnitFoundFlg" = "'true'"!][!//
                [!CALL "CG_FindI2cChannelMappedCoreId", "I2cChannelId" = "node:name(.)"!][!//
                /* I2C[!"$HwUnitIndex"!] assigned to I2cChannel_[!"I2cChannelId"!] in Core[!"$I2cChannelMappedCoreId"!] */
                [!"I2cChannelId"!]U[!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$HwUnitFoundFlg = 'false'"!][!//
            /* I2C[!"$HwUnitIndex"!] not assigned */
            0xFFU[!//
        [!ENDIF!][!//
        [!IF "$HwUnitIndex != num:i(ecu:get('I2c.NumofAvailableI2c') - 1)"!],[!ENDIF!]
    [!ENDINDENT!][!//
    [!ENDFOR!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//


[!/*****************************************************************************
  MACRO: CG_GeneI2cChannelIdMacro
  Generate the macro definition for I2C channel name
*****************************************************************************/!]
[!MACRO "CG_GeneI2cChannelIdMacro"!][!//
[!//
[!INDENT "0"!][!//
    [!LOOP "I2cGlobalConfig/I2cChannel/*"!][!//
        [!CALL "CG_FindI2cChannelMappedCoreId", "I2cChannelId" = "node:name(.)"!][!//
        #ifndef I2cConf_I2cChannel_[!"node:name(.)"!]
        /* I2C Channel ID [!"./I2cChannelId"!] -> [!"name(.)"!], mapped to [!"./I2cHwUnit"!] in Core[!"$I2cChannelMappedCoreId"!] */
        #define I2cConf_I2cChannel_[!"node:name(.)"!]                               ([!"num:i(node:value(./I2cChannelId))"!]U)
        #define I2C_HWUNIT_CHANNEL[!"substring-after(./I2cHwUnit,'I2C')"!]
        #endif
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDMACRO!][!//

[!ENDIF!][!// avoid multiple inclusion ENDIF
[!ENDNOCODE!][!//


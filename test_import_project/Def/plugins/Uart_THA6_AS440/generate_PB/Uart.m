[!NOCODE!][!//
/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Uart_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Uart
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

[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!/* avoid multiple inclusion */!]
[!IF "not(var:defined('UART_CFG_COMMON_M'))"!]
[!VAR "UART_CFG_COMMON_M"="'true'"!]

[!NOCODE!][!//
[!IF "not(node:exists(as:modconf('Resource')[1]))"!][!//
[!ERROR!][!//
    [255-03-06-ERROR]: UART Code Generator: Resource module is not added to the project.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!/*****************************************************************************
  MACRO: CG_FindUartChannelMappedCoreId
  To find the CoreId according to the Uart channel
*****************************************************************************/!]
[!MACRO "CG_FindUartChannelMappedCoreId", "UartChannelName" = ""!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "ModuleName" = "'UART'"!][!//
    [!VAR "UartChannelMappedCoreId" = "num:i(0)"!][!//
    [!VAR "UartChannelMappedFlag" = "'false'"!][!//
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
                        [!IF "$UartChannelName = $Resource_ModuleName"!][!//
                            [!VAR "UartChannelMappedCoreId" = "num:i(text:split($Resource_CoreId, 'CORE')[1])"!][!//
                            [!VAR "UartChannelMappedFlag" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!ERROR!][!//
                            [255-03-07-ERROR]: Invalid resource allocation done in [!"$Resource_CoreId"!] for [!"$ModuleName"!] module:[!"node:path(.)"!][!//
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!IF "$UartChannelMappedFlag = 'false'"!][!//
        [!/* If not allocated the Uart channel to any core will default allocate to core0 */!][!//
        [!VAR "UartChannelMappedCoreId" = "num:i(0)"!][!//
    [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: Uart_ChangeStrMember
    Object: StringList operation object, whose members are in the form of key-value pairs in the form of <key:KeyValue>
    Index : StringList member subscript index value
    Value : ''    : Perform +1 processing on the member with index in Object
            $Value: Use "$Value" to replace the indexed member in Object
*****************************************************************************/!]
[!MACRO "Uart_ChangeStrMember", "Object" = "", "Index" = "", "Value" = ""!][!//
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
  MACRO: CG_FindTotalNumUartChannelMappedToCorex
  Find which core used for Uart channel
*****************************************************************************/!]
[!MACRO "CG_FindTotalNumUartChannelMappedToCorex"!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "UartChannelTotalNumCorex" = "''"!][!//
    [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        [!VAR "UartChannelTotalNumCorex" = "concat($UartChannelTotalNumCorex, $CoreIndex, ':0 ')"!][!//
    [!ENDFOR!][!//
    [!LOOP "node:order(UartGlobalConfig/UartChannel/*, 'UartChannelId')"!][!//
        [!CALL "CG_FindUartChannelMappedCoreId", "UartChannelName"="node:name(.)"!][!//
        [!IF "$UartChannelMappedCoreId != num:i(255)"!][!//
            [!CALL "Uart_ChangeStrMember", "Object"="$UartChannelTotalNumCorex", "Index" = "$UartChannelMappedCoreId", "Value" = "''"!][!//
            [!VAR "UartChannelTotalNumCorex" = "$ReturnObject"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!CALL "CG_FindTotalNumUartChannelMappedToCorex"!]
[!/*****************************************************************************
  MACRO: CG_GeneUartHwUnitConfig
  Generate UART channel hardware config information
*****************************************************************************/!]
[!MACRO "CG_GeneUartHwUnitConfig", "CoreID" = ""!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!VAR "CorexUartNum" = "num:i(0)"!][!//
    [!/* Generated in ascending of Uart channels */!][!//
    [!LOOP "node:order(UartGlobalConfig/UartChannel/*, 'UartChannelId')"!][!//
        [!CALL "CG_FindUartChannelMappedCoreId", "UartChannelName"="node:name(.)"!][!//
        [!IF "num:i($UartChannelMappedCoreId) = $CoreID"!][!//
            [!VAR "CorexUartNum" = "num:i($CorexUartNum + 1)"!][!//
            [!SELECT "as:modconf('Uart')[1]"!][!//
            [!VAR "UartSysClock" = "node:value(node:ref(UartClockSet/UartSysClockRef)/McuClockReferencePointFrequency)"!][!//
            [!ENDSELECT!][!//
            [!INDENT "4"!][!//
            /* [!"./UartHwUnit"!] used by [!"node:name(.)"!]*/
            {
                [!INDENT "8"!][!//
                    [!VAR "BaudRateRegValue" = "num:f($UartSysClock div UartChannelBaudRate)"!][!//
                    /* Baud-rate ratio: Clock[[!"$UartSysClock"!]]/baud-rate[[!"UartChannelBaudRate"!]]/RegisterValue[[!"$BaudRateRegValue div 16"!]] */
                    /* Integer Baud rate */
                    [!"num:i($BaudRateRegValue div 16)"!]U,
                    /* Fractional Baud rate */
                    [!"num:i(num:f(num:f($BaudRateRegValue div 16) - num:i(num:f($BaudRateRegValue div 16))) * 16)"!]U,
                    /* Enable/disable RX/TX/Error interrupt */
                    [!IF "./UartRxInterruptEnable != 'true' and ./UartTxInterruptEnable != 'true' and ./UartErrorInterruptEnable != 'true'"!][!//
                        ASI_UART_NO_INT,
                    [!ENDIF!][!//
                    [!IF "./UartRxInterruptEnable = 'true'"!][!//
                        ASI_UART_DATA_RX_COMPLETE_INT[!//
                        [!IF "./UartTxInterruptEnable != 'true' and ./UartErrorInterruptEnable != 'true'"!][!//
                        ,
                        [!ELSE!][!//
                        [!WS!]| [!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    [!IF "./UartTxInterruptEnable = 'true'"!][!//
                        ASI_UART_DATA_TRANSMITTED_INT[!//
                        [!IF "./UartErrorInterruptEnable != 'true'"!][!//
                        ,
                        [!ELSE!][!//
                        [!WS!]| [!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    [!IF "./UartErrorInterruptEnable = 'true'"!][!//
                        ASI_UART_ALL_ERROR_INTS,
                    [!ENDIF!][!//
                    /* The number of over sample */
                    ASI_UART_SAMPLENUM_16,
                    /* The number of data bit */
                    ASI_[!"UartDataBitWidth"!],
                    /* The number of stop bit */
                    ASI_[!"UartStopBitWidth"!],
                    /* Parity control: no parity, even, odd, logic 0, logic 1 */
                    ASI_[!"UartDataParityMode"!],
                    /* Buffer works in  [!IF "UartDMAEnable = 'true'"!]FIFO mode and enable DMA[!ELSE!]Buffer mode and disable DMA[!ENDIF!]  */
                    [!IF "UartDMAEnable = 'true'"!]TRUE,[!ELSE!]FALSE,[!ENDIF!]
                    /* Enable/disable RX buffer lock mode */
                    [!IF "UartBufferLockModeEnable = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!]
                [!ENDINDENT!][!//
            }[!IF "$CorexUartNum != $UartChannelNumCorex"!],[!ENDIF!]
            [!ENDINDENT!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GeneUartChannelConfig
  Generate UART Channel config information
*****************************************************************************/!]
[!MACRO "CG_GeneUartChannelConfig", "CoreID" = ""!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!VAR "CorexUartNum" = "num:i(0)"!][!//
    [!VAR "TotalChannelNum" = "num:i(count(UartGlobalConfig/UartChannel/*))"!][!//
    [!FOR "ChannelIndex" = "0" TO "num:i($TotalChannelNum - 1)"!][!//
        [!/* Generated in ascending of Uart Channels */!][!//
        [!LOOP "node:order(UartGlobalConfig/UartChannel/*, 'UartChannelId')"!][!//
            [!IF "UartChannelId = $ChannelIndex"!][!//
                [!CALL "CG_FindUartChannelMappedCoreId", "UartChannelName"="node:name(.)"!][!//
                [!IF "num:i($UartChannelMappedCoreId) = $CoreID"!][!//
                    [!INDENT "4"!][!//
                    {
                        [!INDENT "8"!][!//
                        /* Uart Channel ID (Name: [!"node:name(.)"!]) */
                        [!"UartChannelId"!]U,
                        /* ASI HwUnit([!"UartHwUnit"!]) of assigned to Uart channel (Name: [!"node:name(.)"!]) */
                        [!"text:split(UartHwUnit, 'ASI')[1]"!]U,
                        /* Uart channel transmission data width (byte) */
                        [!IF "text:split(./UartDataBitWidth, '_')[last()] > num:i(8)"!][!//
                            2U,
                        [!ELSE!][!//
                            1U,
                        [!ENDIF!][!//
                        /* Receive interrupt handling function */
                        [!IF "node:exists(./UartRxNotification)"!][!//
                            [!"node:value(./UartRxNotification)"!],
                        [!ELSE!][!//
                            NULL_PTR,
                        [!ENDIF!][!//
                        /* Transmit interrupt handling function */
                        [!IF "node:exists(./UartTxNotification)"!][!//
                            [!"node:value(./UartTxNotification)"!],
                        [!ELSE!][!//
                            NULL_PTR,
                        [!ENDIF!][!//
                        /* Error interrupt handling function */
                        [!IF "node:exists(./UartErrorNotification)"!][!//
                            [!"node:value(./UartErrorNotification)"!],
                        [!ELSE!][!//
                            NULL_PTR,
                        [!ENDIF!][!//
                        /* The configuration information structure of the hardware unit([!"UartHwUnit"!]) (Name: [!"node:name(.)"!]) */
                        &Uart_HWUnitConfigSetCore[!"$CoreIndex"!][[!"$CorexUartNum"!]]
                        [!ENDINDENT!][!//
                        [!VAR "CorexUartNum" = "num:i($CorexUartNum + 1)"!][!//
                    }[!IF "$CorexUartNum != $UartChannelNumCorex"!],[!ENDIF!]
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
  Generate UART channel hardware config information
*****************************************************************************/!]
[!MACRO "CG_GeneChannelToCoreMap"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!INDENT "4"!][!//
    [!VAR "UartChannelMappedCorex" = "''"!][!//
    [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        [!VAR "UartChannelMappedCorex" = "concat($UartChannelMappedCorex, $CoreIndex, ':255 ')"!][!//
    [!ENDFOR!][!//
    [!VAR "UartChannelTotalNum" = "count(UartGlobalConfig/UartChannel/*)"!][!//
    [!LOOP "node:order(UartGlobalConfig/UartChannel/*, 'UartChannelId')"!][!//
        [!CALL "CG_FindUartChannelMappedCoreId", "UartChannelName"="node:name(.)"!][!//
        [!VAR "UartChannelIndex" = "substring-after(text:split($UartChannelMappedCorex)[num:i($UartChannelMappedCoreId + 1)], ':')"!][!/* CoreId:Num--->1:2 */!][!//
        [!IF "num:i($UartChannelIndex) = num:i(255)"!][!//
            [!VAR "UartChannelIndex" = "num:i(0)"!][!//
        [!ELSE!][!//
            [!VAR "UartChannelIndex" = "num:i($UartChannelIndex + 1)"!][!//
        [!ENDIF!][!//
        [!CALL "Uart_ChangeStrMember", "Object"="$UartChannelMappedCorex", "Index" = "$UartChannelMappedCoreId", "Value" = "$UartChannelIndex"!][!//
        [!VAR "UartChannelMappedCorex" = "$ReturnObject"!][!//
        /* [!"node:name(.)"!] configuration information is assigned to index[!"num:i($UartChannelIndex)"!] of Core[!"$UartChannelMappedCoreId"!] */
        [!"num:i($UartChannelIndex)"!]U[!IF "node:value(./UartChannelId) < num:i($UartChannelTotalNum - 1)"!],[!ENDIF!]
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GeneHwUnitNumToUartChannel
  Generate UART channel number mapping table corresponding to hardware
*****************************************************************************/!]
[!MACRO "CG_GeneHwUnitNumToUartChannel"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!FOR "HwUnitIndex" = "0" TO "num:i(ecu:get('Asi.MaxHwUnit') - 1)"!][!//
    [!VAR "HwUnitFoundFlg" = "0"!][!//
    [!INDENT "4"!][!//
        [!LOOP "node:order(UartGlobalConfig/UartChannel/*, 'UartChannelId')"!][!//
            [!IF "$HwUnitIndex = text:split(UartHwUnit, 'ASI')[1] "!][!//
                [!VAR "HwUnitFoundFlg" = "1"!][!//
                [!CALL "CG_FindUartChannelMappedCoreId", "UartChannelName" = "node:name(.)"!][!//
                /* ASI[!"$HwUnitIndex"!] assigned to [!"node:name(.)"!] in Core[!"$UartChannelMappedCoreId"!] */
                [!"UartChannelId"!]U[!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$HwUnitFoundFlg = 0"!][!//
            /* ASI[!"$HwUnitIndex"!] not assigned */
            0xFFU[!//
        [!ENDIF!][!//
        [!IF "$HwUnitIndex != num:i(ecu:get('Asi.MaxHwUnit') - 1)"!],[!ENDIF!]
    [!ENDINDENT!][!//
    [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//


[!/*****************************************************************************
  MACRO: CG_GeneHwUnitMap
  Generate Uart available ASI hardware unit mapping table.
*****************************************************************************/!]
[!MACRO "CG_GeneHwUnitMap"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!FOR "HwUnitIndex" = "0" TO "num:i(ecu:get('Asi.MaxHwUnit') - 1)"!][!//
        [!INDENT "4"!][!//
            /* #Violation: Uart_PBcfg_c_REF_2 */
            ASI[!"$HwUnitIndex"!][!IF "$HwUnitIndex != num:i(ecu:get('Asi.MaxHwUnit') - 1)"!],[!ELSE!][!WS!][!ENDIF!][!WS "8"!]/* ASI[!"$HwUnitIndex"!] is available*/
        [!ENDINDENT!][!//
    [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GeneUartChannelIdMacro
  Generate the macro definition for UART channel name
*****************************************************************************/!]
[!MACRO "CG_GeneUartChannelIdMacro"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!LOOP "node:order(UartGlobalConfig/UartChannel/*, 'UartChannelId')"!][!//
        [!CALL "CG_FindUartChannelMappedCoreId", "UartChannelName" = "node:name(.)"!][!//
#ifndef UartConf_[!"node:name(..)"!]_[!"node:name(.)"!]
/* UartChannelId: [!"./UartChannelId"!] -> [!"name(.)"!], mapped to [!"./UartHwUnit"!] in Core[!"$UartChannelMappedCoreId"!] */
#define UartConf_[!"node:name(..)"!]_[!"node:name(.)"!][!WS "8"!]([!"num:i(node:value(./UartChannelId))"!]U)
#endif
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//


[!/*****************************************************************************
  MACRO: CG_GenerateChannelNotification
  Declare the Rx/Tx/Error notification function name
*****************************************************************************/!]
[!MACRO "CG_GenerateChannelNotification"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!IF "node:exists(UartGlobalConfig/UartChannel/*[UartRxInterruptEnable = 'true'])"!][!//
        [!LOOP "node:order(UartGlobalConfig/UartChannel/*, 'UartChannelId')"!][!//
            [!IF "node:exists(./UartRxNotification) and node:value(./UartRxNotification) != 'NULL_PTR'"!][!//
                /* UartChannel[!"./UartChannelId"!]([!"./UartHwUnit"!]) receiving Notification Function Declartion */
                extern void [!"node:value(./UartRxNotification)"!](uint16 RxData);
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!/* line feed */!]
    [!ENDIF!][!//
    [!/* line feed */!][!//
    [!IF "node:exists(UartGlobalConfig/UartChannel/*[UartTxInterruptEnable = 'true'])"!][!//
        [!LOOP "node:order(UartGlobalConfig/UartChannel/*, 'UartChannelId')"!][!//
            [!IF "node:exists(./UartTxNotification) and node:value(./UartTxNotification) != 'NULL_PTR'"!][!//
                /* UartChannel[!"./UartChannelId"!]([!"./UartHwUnit"!]) transmit Notification Function Declartion */
                extern void [!"node:value(./UartTxNotification)"!](void);
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!/* line feed */!]
    [!ENDIF!][!//
    [!/* line feed */!][!//
    [!IF "node:exists(UartGlobalConfig/UartChannel/*[UartErrorInterruptEnable = 'true'])"!][!//
        [!LOOP "node:order(UartGlobalConfig/UartChannel/*, 'UartChannelId')"!][!//
            [!IF "node:exists(./UartErrorNotification) and node:value(./UartErrorNotification) != 'NULL_PTR'"!][!//
                /* UartChannel[!"./UartChannelId"!]([!"./UartHwUnit"!]) ErrorNotification Function Declartion */
                extern void [!"node:value(./UartErrorNotification)"!](uint32 Value);
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_GenerateInterruptEnableMacro
  Generate the macro definition for UART channel RX/TX/ERROR interrupt enable Macro
*****************************************************************************/!]
[!MACRO "CG_GenerateInterruptEnableMacro"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!IF "node:exists(UartGlobalConfig/UartChannel/*[UartRxInterruptEnable = 'true'])"!][!//
        /*
        Configuration: UART_CFG_RX_INTERRUPT_ENABLE
        - if Selected, There is a Uart channel to enable receive interrupt
        - if Deselected, There is no Uart channel to enable receive interrupt
        */
        #define UART_CFG_RX_INTERRUPT_ENABLE   [!WS "10"!](STD_ON)

        /*
        Configuration: UART_USED_RX_INTC_ASIx
        Define the HwUnit of the ASI occupied by the UART driver.
        */
        [!LOOP "node:order(UartGlobalConfig/UartChannel/*, 'UartHwUnit')"!][!//
            [!IF "./UartRxInterruptEnable = 'true'"!][!//
                #define UART_USED_RX_INTC_ASI[!"substring-after(./UartHwUnit, 'ASI')"!]    [!WS "15"!](STD_ON)
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!/* line feed */!]
    [!ELSE!]
        /*
        Configuration: UART_CFG_RX_INTERRUPT_ENABLE
        - if Selected, There is a Uart channel to enable receive interrupt
        - if Deselected, There is no Uart channel to enable receive interrupt
        */
        #define UART_CFG_RX_INTERRUPT_ENABLE   [!WS "10"!](STD_OFF)
        [!/* line feed */!]
    [!ENDIF!][!//
    [!/* line feed */!][!//
    [!IF "node:exists(UartGlobalConfig/UartChannel/*[UartTxInterruptEnable = 'true'])"!][!//
        /*
        Configuration: UART_CFG_TX_INTERRUPT_ENABLE
        - if Selected, There is a Uart channel to enable transmit interrupt
        - if Deselected, There is no Uart channel to enable transmit interrupt
        */
        #define UART_CFG_TX_INTERRUPT_ENABLE   [!WS "10"!](STD_ON)

        /*
        Configuration: UART_USED_TX_INTC_ASIx
        Define the HwUnit of the ASI occupied by the UART driver.
        */
        [!LOOP "node:order(UartGlobalConfig/UartChannel/*, 'UartHwUnit')"!][!//
            [!IF "./UartTxInterruptEnable = 'true'"!][!//
                #define UART_USED_TX_INTC_ASI[!"substring-after(./UartHwUnit, 'ASI')"!]    [!WS "15"!](STD_ON)
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!/* line feed */!]
    [!ELSE!]
        /*
        Configuration: UART_CFG_TX_INTERRUPT_ENABLE
        - if Selected, There is a Uart channel to enable transmit interrupt
        - if Deselected, There is no Uart channel to enable transmit interrupt
        */
        #define UART_CFG_TX_INTERRUPT_ENABLE   [!WS "10"!](STD_OFF)
    [!ENDIF!]
    [!/* line feed */!][!//
    [!IF "node:exists(UartGlobalConfig/UartChannel/*[UartErrorInterruptEnable = 'true'])"!][!//
        /*
        Configuration: UART_CFG_ERROR_INTERRUPT_ENABLE
        - if Selected, There is a Uart channel to enable error interrupt
        - if Deselected, There is no Uart channel to enable error interrupt
        */
        #define UART_CFG_ERROR_INTERRUPT_ENABLE  [!WS "8"!](STD_ON)

        /*
        Configuration: UART_USED_ERROR_INTC_ASIx
        Define the HwUnit of the ASI occupied by the UART driver.
        */
        [!LOOP "node:order(UartGlobalConfig/UartChannel/*, 'UartHwUnit')"!][!//
            [!IF "./UartErrorInterruptEnable = 'true'"!][!//
                #define UART_USED_ERROR_INTC_ASI[!"substring-after(./UartHwUnit, 'ASI')"!]    [!WS "12"!](STD_ON)
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!/* line feed */!]
    [!ELSE!]
        /*
        Configuration: UART_CFG_ERROR_INTERRUPT_ENABLE
        - if Selected, There is a Uart channel to enable error interrupt
        - if Deselected, There is no Uart channel to enable error interrupt
        */
        #define UART_CFG_ERROR_INTERRUPT_ENABLE  [!WS "8"!](STD_OFF)
    [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//



[!ENDIF!]
[!ENDNOCODE!][!//
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Can_Cfg_Common.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : MCAN
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
[!IF "not(var:defined('CAN_CFG_COMMON_M'))"!]
[!VAR "CAN_CFG_COMMON_M"="'true'"!]

[!NOCODE!][!//
[!IF "not(node:exists(as:modconf('Resource')[1]))"!][!//
[!ERROR!][!//
    080-00-01-ERROR: CAN Code Generator: Resource module is not added to the project.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//

[!/*****************************************************************************
  MACRO: CG_FindCanControllerMappedCoreId
  To find the CoreId according to the Can Controller
*****************************************************************************/!]
[!MACRO "CG_FindCanControllerMappedCoreId", "CanControllerName" = ""!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "ModuleName" = "'CAN'"!][!//
    [!VAR "CanControllerMappedCoreId" = "num:i(0)"!][!//
    [!VAR "CanControllerMappedFlag" = "'false'"!][!//
    [!SELECT "as:modconf('Resource')[1]"!][!//
    [!LOOP "ResourceCoreConfigSet/ResourceCoreConfig/*"!][!//
        [!IF "./ResourceCoreEnable = 'true'"!][!//
        [!VAR "Resource_CoreId" = "./ResourceCoreId"!][!//
            [!LOOP "ResourceAllocation/*"!][!//
                [!IF "./ResourceModule = $ModuleName"!][!//
                    [!IF "node:refvalid(./ResourceModuleRef) = 'true'"!][!//
                        [!IF "$CanControllerName = text:split(./ResourceModuleRef, '/')[last()]"!][!//
                            [!VAR "CanControllerMappedCoreId" = "num:i(text:split($Resource_CoreId, 'CORE')[1])"!][!//
                            [!VAR "CanControllerMappedFlag" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!ERROR!][!//
                            080-00-02-ERROR: Invalid resource allocation done in [!"$Resource_CoreId"!] for [!"$ModuleName"!] module:[!"node:path(.)"!][!//
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//


[!/*****************************************************************************
  MACRO: CG_FindCanHardwareObjectIdMappedCoreId
   To find the CoreId according to the Can Hardware Object
*****************************************************************************/!]
[!MACRO "CG_FindCanHardwareObjectIdMappedCoreId", "CanHwObjName" = ""!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "CanHardwareObjectIdMappedCoreId" = "num:i(0)"!][!//
    [!SELECT "as:modconf('Can')[1]"!][!//
        [!LOOP "node:order(CanConfigSet/CanHardwareObject/*, './CanObjectId')"!][!//
            [!IF "$CanHwObjName = node:name(.)"!][!//
                [!CALL "CG_FindCanControllerMappedCoreId", "CanControllerName"="node:name(node:ref(./CanControllerRef))"!][!//
                [!VAR "CanHardwareObjectIdMappedCoreId" = "$CanControllerMappedCoreId"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDSELECT!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_ChangeStringListMember
    Perform Add 'Count' processing on the member with index in Object
    Object: StringList operation object, whose members are in the form of key-value pairs in the form of <Index:Value>, default value <Index:65535>
    Index : StringList member subscript index value
    Count : Increase numerical value
*****************************************************************************/!]
[!MACRO "CG_ChangeStringListMember", "Object" = "", "Index" = "", "Count" = ""!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "Value" = "substring-after(text:split($Object)[num:i($Index + 1)], ':')"!][!//
    [!/* Return the count value in advance before accumulation if need.*/!][!//
    [!VAR "ValueCountBefore" = "$Value"!][!//
    [!VAR "BeforeListText" = "substring-before($Object, concat($Index, ':'))"!][!//
    [!VAR "AfterListText" = "substring-after($Object, concat($Index, ':', string(substring-after(text:split($Object)[num:i($Index + 1)], ':'))))"!][!//
    [!/* The count starts from 0, and when the initial count Count is greater than 1, it needs to be decremented by 1.*/!][!//
    [!IF "num:i($Value) = num:i(65535)"!][!//
        [!VAR "Value" = "num:i($Count - 1)"!][!//
    [!ELSE!][!//
        [!VAR "Value" = "num:i($Value + $Count)"!][!//
    [!ENDIF!][!//
    [!VAR "Object" = "concat($BeforeListText, concat($Index , ':', num:i($Value)), $AfterListText)"!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_FindTotalNumCanControllerMappedToCorex
  To find which core used for Can Controller
*****************************************************************************/!]
[!MACRO "CG_FindTotalNumCanControllerMappedToCorex"!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!/* Create an initial string based on the number of cores: Store in the form of a key-value pair CoreId: The number of resources allocated to the current core (recorded starting from 0) */!][!//
    [!/* CanControllerMappedToCorex-->>Core0Id:ResourcesNumber ... CorexId:ResourcesNumber-->>0:65535 1:65535 2:65535 3:65535 */!][!//
    [!VAR "CanControllerMappedToCorex" = "''"!][!//
    [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        [!VAR "CanControllerMappedToCorex" = "concat($CanControllerMappedToCorex, $CoreIndex, ':65535 ')"!][!//
    [!ENDFOR!][!//
    [!LOOP "node:order(CanConfigSet/CanController/*, './CanControllerId')"!][!//
        [!CALL "CG_FindCanControllerMappedCoreId", "CanControllerName"="node:name(.)"!][!//
        [!CALL "CG_ChangeStringListMember", "Object"="$CanControllerMappedToCorex", "Index" = "$CanControllerMappedCoreId", "Count" = "1"!][!//
        [!VAR "CanControllerMappedToCorex" = "$Object"!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: CG_FindTotalHohNumMappedToCorex
  Count the used MB number map to the Core
*****************************************************************************/!]
[!MACRO "CG_FindTotalHohNumMappedToCorex"!][!//
[!//
[!NOCODE!][!//
[!INDENT "0"!][!//
    [!VAR "TotalHOHNumToCorex" = "''"!][!//
    [!VAR "TotalHRHNumToCorex" = "''"!][!//
    [!VAR "TotalHTHNumToCorex" = "''"!][!//
    [!VAR "TotalHOHUsedElementsNumToCorex" = "''"!][!//
    [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        [!VAR "TotalHOHNumToCorex" = "concat($TotalHOHNumToCorex, $CoreIndex, ':65535 ')"!][!//
        [!VAR "TotalHRHNumToCorex" = "concat($TotalHRHNumToCorex, $CoreIndex, ':65535 ')"!][!//
        [!VAR "TotalHTHNumToCorex" = "concat($TotalHTHNumToCorex, $CoreIndex, ':65535 ')"!][!//
        [!VAR "TotalHOHUsedElementsNumToCorex" = "concat($TotalHOHUsedElementsNumToCorex, $CoreIndex, ':65535 ')"!][!//
    [!ENDFOR!][!//
    [!LOOP "node:order(CanConfigSet/CanHardwareObject/*, './CanObjectId')"!][!//
        [!CALL "CG_FindCanHardwareObjectIdMappedCoreId", "CanHwObjName"="node:name(.)"!][!//
        [!CALL "CG_ChangeStringListMember", "Object"="$TotalHOHNumToCorex", "Index" = "$CanControllerMappedCoreId" ,"Count" = "1"!][!//
        [!VAR "TotalHOHNumToCorex" = "$Object"!][!//
        [!CALL "CG_ChangeStringListMember", "Object"="$TotalHOHUsedElementsNumToCorex", "Index" = "$CanControllerMappedCoreId", "Count" = "node:value(./CanHwObjectCount)"!][!//
        [!VAR "TotalHOHUsedElementsNumToCorex" = "$Object"!][!//
        [!IF "./CanObjectType = 'RECEIVE'"!][!//
            [!CALL "CG_ChangeStringListMember", "Object"="$TotalHRHNumToCorex", "Index" = "$CanControllerMappedCoreId", "Count" = "1"!][!//
            [!VAR "TotalHRHNumToCorex" = "$Object"!][!//
        [!ELSEIF "./CanObjectType = 'TRANSMIT'"!][!//
            [!CALL "CG_ChangeStringListMember", "Object"="$TotalHTHNumToCorex", "Index" = "$CanControllerMappedCoreId", "Count" = "1"!][!//
            [!VAR "TotalHTHNumToCorex" = "$Object"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/* Call the function of CG_FindTotalHohNumMappedToCorex to count the number of Hoh map to core*/!][!//
[!CALL "CG_FindTotalHohNumMappedToCorex"!][!//


[!NOCODE!][!//
[!VAR "TX_INT_FLAG"="0"!][!//
[!VAR "TX_POLL_FLAG"="0"!][!//
[!VAR "RX_INT_FLAG"="0"!][!//
[!VAR "RX_POLL_FLAG"="0"!][!//
[!VAR "BUSOFF_INT_FLAG"="0"!][!//
[!VAR "BUSOFF_POLL_FLAG"="0"!][!//
[!VAR "WAKEUP_INT_FLAG"="0"!][!//
[!VAR "WAKEUP_POLL_FLAG"="0"!][!//
[!VAR "RXFIFO_INT_FLAG"="0"!][!//
[!VAR "RXFIFO_POLL_FLAG"="0"!][!//
[!IF "num:i(count(CanConfigSet/CanController/*[CanTxProcessing = 'INTERRUPT'])) > 0 or num:i(count(CanConfigSet/CanController/*[CanTxProcessing = 'MIXED'])) > 0"!][!//
[!VAR "TX_INT_FLAG"="1"!][!//
[!ENDIF!][!//
[!IF "num:i(count(CanConfigSet/CanController/*[CanTxProcessing = 'POLLING'])) > 0 or num:i(count(CanConfigSet/CanController/*[CanTxProcessing = 'MIXED'])) > 0"!][!//
[!VAR "TX_POLL_FLAG"="1"!][!//
[!ENDIF!][!//
[!IF "num:i(count(CanConfigSet/CanController/*[CanRxProcessing = 'INTERRUPT'])) > 0 or num:i(count(CanConfigSet/CanController/*[CanRxProcessing = 'MIXED'])) > 0"!][!//
[!VAR "RX_INT_FLAG"="1"!][!//
[!VAR "RXFIFO_INT_FLAG"="1"!][!//
[!ENDIF!][!//
[!IF "num:i(count(CanConfigSet/CanController/*[CanRxProcessing = 'POLLING'])) > 0 or num:i(count(CanConfigSet/CanController/*[CanRxProcessing = 'MIXED'])) > 0"!][!//
[!VAR "RX_POLL_FLAG"="1"!][!//
[!VAR "RXFIFO_POLL_FLAG"="1"!][!//
[!ENDIF!][!//
[!IF "num:i(count(CanConfigSet/CanController/*[CanBusoffProcessing = 'INTERRUPT'])) > 0"!][!//
[!VAR "BUSOFF_INT_FLAG"="1"!][!//
[!ENDIF!][!//
[!IF "num:i(count(CanConfigSet/CanController/*[CanBusoffProcessing = 'POLLING'])) > 0"!][!//
[!VAR "BUSOFF_POLL_FLAG"="1"!][!//
[!ENDIF!][!//
[!IF "num:i(count(CanConfigSet/CanController/*[CanWakeupProcessing = 'INTERRUPT'])) > 0"!][!//
[!VAR "WAKEUP_INT_FLAG"="1"!][!//
[!ENDIF!][!//
[!IF "num:i(count(CanConfigSet/CanController/*[CanWakeupProcessing = 'POLLING'])) > 0"!][!//
[!VAR "WAKEUP_POLL_FLAG"="1"!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//

[!VAR "WakeUp_Support_Flag"="0"!]
[!VAR "CANFD_Support_Flag"="0"!]
[!LOOP "CanConfigSet/CanController/*"!]
    [!IF "node:exists(CanWakeupSupport)"!]
        [!VAR "WakeUp_Support_Flag"="1"!]
    [!ENDIF!]
    [!IF "node:exists(CanFDSupport)"!]
        [!VAR "CANFD_Support_Flag"="1"!]
    [!ENDIF!]
[!ENDLOOP!]

[!VAR "CanFD_Controller_Supported" = "0"!][!//
[!IF "($CANFD_Support_Flag = 1) and (num:i(count(CanConfigSet/CanController/*[CanFDSupport = 'true'])) > 0)"!][!//
[!VAR "CanFD_Controller_Supported" = "1"!][!//
[!ENDIF!]

[!VAR "Can_Wakeup_Controller_Supported" = "0"!][!//
[!IF "($WakeUp_Support_Flag = 1) and (num:i(count(CanConfigSet/CanController/*[CanWakeupSupport = 'true'])) > 0)"!][!//
[!VAR "Can_Wakeup_Controller_Supported" = "1"!][!//
[!ENDIF!]

[!/* Check status of CanHwFilter and CanMainFunctionRWPeriodRef */!]
[!SELECT "CanConfigSet"!]
    [!LOOP "CanHardwareObject/*"!]
        [!IF "(((CanObjectType = 'RECEIVE') and ((node:ref(CanControllerRef)/CanRxProcessing) = 'POLLING')) or ((CanObjectType = 'TRANSMIT') and (node:value((node:ref(CanControllerRef)/CanTxProcessing)) = 'POLLING'))) and (not(node:exists(CanMainFunctionRWPeriodRef)))"!]
            [!ERROR!]
                080-00-04-ERROR: [!"node:name(.)"!] --> The "CanMainFunctionRWPeriodRef" must be enabled when user configure the Can controller operate in the POLLING mode (both to transmission and reception)
            [!ENDERROR!]
        [!ENDIF!]
        [!IF "((CanObjectType = 'RECEIVE')) and (not(node:exists(CanHwFilter)))"!]
            [!ERROR!]
            080-00-05-ERROR: The "CanHwFilter" of each HOH must be enabled when user configure HOH is receive.
            [!ENDERROR!]
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDSELECT!]


[!ENDIF!][!// avoid multiple inclusion ENDIF
[!ENDNOCODE!][!//

[!INDENT "0"!][!//
[!/* To find the Ram message index according to the Can Controller */!][!//
[!MACRO "CG_CalculateDedicatedBuffElementIndex", "CanCtrlId" = ""!][!//
    [!VAR "RxDedicatedBuffIndex" = "num:i(0)"!][!//
    [!VAR "TxDedicatedBuffIndex" = "num:i(0)"!][!//
    [!VAR "CurrentObjID" = "num:i(CanObjectId)"!][!//
    [!LOOP "node:order(../../CanHardwareObject/*, 'node:value(CanObjectId)')"!][!//
      [!/* The Element Index starts counting from 0 and must stop iterating when it reaches the current mailbox */!][!//
      [!IF "node:value(CanObjectId) = $CurrentObjID"!][!BREAK!][!ENDIF!][!//
      [!IF "CanObjectType = 'TRANSMIT'"!][!//
          [!IF "(CanHwObjectCount = '1') and (num:i(node:ref(CanControllerRef)/CanControllerId) = $CanCtrlId)"!][!//
            [!VAR "TxDedicatedBuffIndex" = "num:i($TxDedicatedBuffIndex + 1)"!][!//
          [!ENDIF!][!//
      [!ELSEIF "CanObjectType = 'RECEIVE'"!][!//
          [!IF "(CanHwObjectCount = '1') and (num:i(node:ref(CanControllerRef)/CanControllerId) = $CanCtrlId)"!][!//
            [!VAR "RxDedicatedBuffIndex" = "num:i($RxDedicatedBuffIndex + 1)"!][!//
          [!ENDIF!][!//
      [!ELSE!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!/* To find the TxFifo/Queue message index according to the Can Controller */!][!//
[!MACRO "CG_CalculateTxFifoElementIndex", "CanCtrlId" = ""!][!//
    [!VAR "TxFiFoQueueElementIndex" = "num:i(0)"!][!//
    [!LOOP "node:order(../../CanHardwareObject/*, 'node:value(CanObjectId)')"!][!//
      [!/* In case of mixed configurations where dedicated Tx Buffers are combined with a Tx FIFO
        or a Tx Queue, the Put and Get Indices indicate the number of the Tx Buffer starting with
        the first dedicated Tx Buffers.
        Example: For a configuration of 12 dedicated Tx Buffers and a Tx FIFO of 20 Buffers a
        Put Index of 15 points to the fourth buffer of the Tx FIFO. */!][!//
      [!IF "CanObjectType = 'TRANSMIT'"!][!//
          [!IF "(CanHwObjectCount = 1) and (num:i(node:ref(CanControllerRef)/CanControllerId) = $CanCtrlId)"!][!//
            [!VAR "TxFiFoQueueElementIndex" = "num:i($TxFiFoQueueElementIndex + 1)"!][!//
          [!ENDIF!][!//
      [!ELSE!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!/* To find the RxFifo number according to the Can Controller */!][!//
[!MACRO "CG_CalculateRxFifoNumber", "CanCtrlId" = ""!][!//
    [!VAR "RxFifoNumber" = "num:i(0)"!][!//
    [!VAR "CurrentObjID" = "num:i(CanObjectId)"!][!//
    [!LOOP "node:order(../../CanHardwareObject/*, 'node:value(CanObjectId)')"!][!//
      [!/* The Element Index starts counting from 0 and must stop iterating when it reaches the current mailbox */!][!//
      [!IF "node:value(CanObjectId) = $CurrentObjID"!][!BREAK!][!ENDIF!][!//
      [!IF "CanObjectType = 'RECEIVE'"!][!//
          [!IF "(CanHwObjectCount > 1) and (num:i(node:ref(CanControllerRef)/CanControllerId) = $CanCtrlId)"!][!//
            [!VAR "RxFifoNumber" = "num:i($RxFifoNumber + 1)"!][!//
          [!ENDIF!][!//
      [!ELSE!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!/* To find the Filter number index according to the Can Controller */!][!//
[!MACRO "CG_CalculateFilternumber", "CanCtrlId" = ""!][!//
    [!VAR "RxStdFilterindex" = "num:i(0)"!][!//
    [!VAR "RxExtFilterindex" = "num:i(0)"!][!//
    [!VAR "RxBufferOffset" = "num:i(0)"!][!//
    [!VAR "CurrentObjID" = "num:i(CanObjectId)"!][!//
    [!LOOP "node:order(../../CanHardwareObject/*, 'node:value(CanObjectId)')"!][!//
        [!IF "node:value(CanObjectId) = $CurrentObjID"!][!BREAK!][!ENDIF!][!//
        [!IF "CanObjectType = 'RECEIVE' and (num:i(node:ref(CanControllerRef)/CanControllerId) = $CanCtrlId)"!][!//
            [!IF "CanIdType = 'STANDARD' or CanIdType = 'MIXED'"!][!//
                [!VAR "RxStdFilterindex" = "num:i($RxStdFilterindex + 1)"!][!//
            [!ENDIF!][!//
            [!IF "CanIdType = 'EXTENDED' or CanIdType = 'MIXED'"!][!//
                [!VAR "RxExtFilterindex" = "num:i($RxExtFilterindex + 1)"!][!//
            [!ENDIF!][!//
            [!IF "CanHwObjectCount = '1'"!][!//
                [!VAR "RxBufferOffset" = "num:i($RxBufferOffset + 1)"!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//


[!INDENT "0"!][!//
[!/* To find the Hardware Channel according to the text */!][!//
[!MACRO "CG_CalculateHardwareChannel", "Channel" = ""!][!//
    [!VAR "ResHardwareNodePerModule" = "num:hextoint(ecu:get('Can.MaxNodes'))"!][!//
    [!VAR "ResHardwareModule" = "num:i(substring($Channel,16,1))"!][!//
    [!VAR "ResHardwareNode" = "num:i(substring($Channel,17,1))"!][!//
    [!VAR "ResHardwareChannel" = "num:i($ResHardwareNodePerModule * $ResHardwareModule + $ResHardwareNode)"!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//
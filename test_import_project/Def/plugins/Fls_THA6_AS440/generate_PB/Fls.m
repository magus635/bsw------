[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Fls.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : DFlash
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
[!/* Caculate the number of FlsSectorList and if the FlsSectorStartaddress is overlapping */!][!//
[!MACRO "CG_CalculateFlsSectorListNumber"!][!//
[!NOCODE!][!//
[!VAR "FlsSectorListNumber" = "num:i(0)"!][!//
[!VAR "FlsSectorPreviousEndAddress" = "num:i(0)"!]
[!VAR "FlsSectorPreviousSectorName" = "''"!]
[!LOOP "node:order(as:modconf('Fls')[1]/FlsConfigSet/FlsSectorList/FlsSector/*, 'FlsSectorStartaddress')"!][!//
    [!VAR "FlsSectorListNumber" = "num:i($FlsSectorListNumber + 1)"!][!//
    [!/* Check if the start address is overlapping with the previous sector */!]
    [!VAR "FlsSectorEndAddress" = "num:i(num:i(./FlsSectorSize) * num:i(./FlsNumberOfSectors) + num:i(./FlsSectorStartaddress) - num:i('1'))"!][!//
    [!IF "num:i(./FlsSectorStartaddress) < $FlsSectorPreviousEndAddress - 1"!][!//
        [!ERROR!][!//
            [!"node:name(.)"!] the 'FlsSectorStartaddress' is overlapping with the [!"$FlsSectorPreviousSectorName"!].
            [!"$FlsSectorPreviousSectorName"!] end at [!"$FlsSectorPreviousEndAddress"!].
            [!"node:name(.)"!] must start at [!"num:i($FlsSectorPreviousEndAddress + 1)"!] at lease.
        [!ENDERROR!][!//
        [!BREAK!][!//
    [!ELSE!]
        [!VAR "FlsSectorPreviousEndAddress" = "num:i($FlsSectorEndAddress)"!][!//
        [!VAR "FlsSectorPreviousSectorName" = "node:name(.)"!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//


[!/* Check if the maximum number of operating bytes of the FLS module is configured correctly in different modes */!][!//
[!MACRO "FLS_CheckMaxOperateNumber"!][!//
[!NOCODE!][!//
[!VAR "FlashPageSize" = "ecu:get('Fls.PageSize')"!][!//
[!VAR "FlsMaxWriteFastMode" =  "./FlsMaxWriteFastMode"!][!//
[!VAR "Temp0" = "$FlsMaxWriteFastMode div $FlashPageSize"!][!//
[!VAR "Temp1" = "num:i($Temp0)"!][!//
[!VAR "Temp2" = "$Temp0 - $Temp1"!][!//
[!IF "$Temp2 != 0"!][!//
[!ERROR!][!//
92-00-02-ERROR: Node FlsMaxWriteFastMode is not set correctly and it should be an integer multiple of the minimum write unit for Flash([!"$FlashPageSize"!]).
[!ENDERROR!][!//
[!ENDIF!][!//

[!VAR "FlsMaxWriteNormalMode" =  "./FlsMaxWriteNormalMode"!][!//
[!VAR "Temp0" = "$FlsMaxWriteNormalMode div $FlashPageSize"!][!//
[!VAR "Temp1" = "num:i($Temp0)"!][!//
[!VAR "Temp2" = "$Temp0 - $Temp1"!][!//
[!IF "$Temp2 != 0"!][!//
[!ERROR!][!//
92-00-03-ERROR: Node FlsMaxWriteNormalMode is not set correctly and it should be an integer multiple of the minimum write unit for Flash([!"$FlashPageSize"!]).
[!ENDERROR!][!//
[!ENDIF!][!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!][!//


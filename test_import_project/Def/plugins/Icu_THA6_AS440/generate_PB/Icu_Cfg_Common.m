[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Icu_Cfg_Common.m
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
***************************************************************************************************/
[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!/* avoid multiple inclusion */!]
[!IF "not(var:defined('ICU_CFG_COMMON_M'))"!]
[!VAR "ICU_CFG_COMMON_M"="'true'"!]

[!NOCODE!][!//
[!IF "not(node:exists(as:modconf('Resource')[1]))"!][!//
[!ERROR!][!//
    [122-00-00-ERROR]: ICU Code Generator: Resource module is not added to the project.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//

[!NOCODE!][!//
[!SELECT "as:modconf('Resource')[1]"!][!//
[!/* Find the master core */!][!//
[!VAR "Resource_MasterCore" = "node:value(ResourceCoreConfigSet/ResourceMasterCore)"!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//




[!INDENT "0"!][!//
[!/* To find the CoreId according to the ICU channel */!][!//
[!MACRO "GetIntcInfo", "HwName" = "","ClusterId" = "","ChId" = "","Mode" = ""!][!//
    [!VAR "IntSrcName" = "concat($HwName,$ClusterId,$ChId)"!][!//
    [!CODE!][!//
        [!VAR "Mode" = "'LEVEL'"!][!//
        [!SELECT "as:modconf('Intc')[1]"!][!//
            [!LOOP "IntcConfigSet/IntcContainer/*/IntcIntSrcSubClassContainer/*/IntcIntSrcContainer/*"!][!//
                [!IF "IntcIntSrcName = $IntSrcName"!][!//
                    [!IF "IntcIntSrcTriggerMethod = 'EDGE'"!][!//
                        [!VAR "Mode" = "'PULSENOTIFY'"!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDSELECT!][!//
        [!ENDCODE!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//





[!INDENT "0"!][!//
[!/* To find the CoreId according to the ICU channel */!][!//
[!MACRO "CG_FindIcuChannelMappedCoreId", "IcuChId" = ""!][!//
    [!VAR "ModuleName" = "'ICU'"!][!//
    [!VAR "IcuchannelMappedCoreId" = "num:i(0)"!][!//
    [!VAR "IcuChannelMappedFlag" = "'false'"!][!//
    [!VAR "IcuchannelMappedRequestCoreId" = "num:i(0)"!][!//
    [!VAR "IcuChannelMappedRequestFlag" = "'false'"!][!//
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
                        [!IF "$IcuChId = $Resource_ModuleName"!][!//
                            [!VAR "IcuchannelMappedCoreId" = "num:i(text:split($Resource_CoreId, 'CORE')[1])"!][!//
                            [!VAR "IcuChannelMappedFlag" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!ERROR!][!//
                            ERROR: [122-00-01-ERROR]: Invalid resource allocation done in [!"$Resource_CoreId"!] for [!"$ModuleName"!] module:[!"node:path(.)"!][!//
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!IF "$IcuChannelMappedFlag = 'false'"!][!//
        [!/* If not allocated the Icu channel to any core will default allocate to core0 */!][!//
        [!VAR "IcuchannelMappedCoreId" = "num:i(0)"!][!//
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//







[!/* Find which core used for Icu channel */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_FindTotalNumIcuChannelMappedToCorex"!][!//
    [!VAR "IcuChannelMappedCore0" = "0"!][!//
    [!VAR "IcuChannelMappedCore1" = "0"!][!//
    [!VAR "IcuChannelMappedCore2" = "0"!][!//
    [!VAR "IcuChannelMappedCore3" = "0"!][!//
    [!VAR "IcuChannelMappedCore4" = "0"!][!//
    [!LOOP "IcuConfigSet/IcuChannel/*"!][!//
        [!CALL "CG_FindIcuChannelMappedCoreId", "IcuChId"="node:name(.)"!][!//
        [!IF "$IcuchannelMappedCoreId = num:i(0)"!][!//
            [!VAR "IcuChannelMappedCore0" = "$IcuChannelMappedCore0 + 1"!][!//
        [!ELSEIF "$IcuchannelMappedCoreId = num:i(1)"!][!//
            [!VAR "IcuChannelMappedCore1" = "$IcuChannelMappedCore1 + 1"!][!//
        [!ELSEIF "$IcuchannelMappedCoreId = num:i(2)"!][!//
            [!VAR "IcuChannelMappedCore2" = "$IcuChannelMappedCore2 + 1"!][!//
        [!ELSEIF "$IcuchannelMappedCoreId = num:i(3)"!][!//
            [!VAR "IcuChannelMappedCore3" = "$IcuChannelMappedCore3 + 1"!][!//
        [!ELSEIF "$IcuchannelMappedCoreId = num:i(4)"!][!//
            [!VAR "IcuChannelMappedCore4" = "$IcuChannelMappedCore4 + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//




[!/* Check and confirm SRC_IN_MUX value */!][!//
[!INDENT "0"!][!//
[!MACRO "AuxCheck"!][!//

[!VAR "ChState" = "'default'"!][!//
[!SELECT "as:modconf('Icu')[1]/IcuConfigSet/IcuChannel"!][!//
[!LOOP "node:order(./*, 'IcuChannelId')"!][!//
    [!IF "./TimChannelInputSelect= 'INPUT_OF_AUX_IN'"!][!//
        [!IF "not(contains(./AuxInSource, 'ATOM')) and not(contains(./AuxInSource, 'N'))"!][!//
            [!VAR "RefChannel" = "./IcuChannelInputSelection"!][!//
            [!VAR "Unit" = "node:ref($RefChannel)/ModuleId"!][!//
            [!VAR "TomUnit" = "substring(node:value(./AuxInSource),5,1)"!][!//
            [!IF "$Unit > '0'"!][!//
                /*IsChIndexBiggerThan8 */
                [!IF "$Unit = $TomUnit"!][!//
                    [!IF "$ChState = 'default'"!][!//
                    [!VAR "ChState" = "'lessThan8'"!][!//
                    [!ELSEIF "$ChState = 'biggerThan8'"!][!//
                    [!ERROR!][!//
                    [122-00-03-ERROR]: IcuChannelId ([!"./IcuChannelId"!]) AuxInSource error! All internal routing TOM channel must be in same group, Group1:{TimXChY choose TomXChY (Y < 8)}. group2 {TimXchY choose TomXchY ( Y < 8)  or  choose  Tom(X-1)ChY ( 0 < X , Y < 16)  ).
                    [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ELSE!][!//
                    [!IF "$ChState = 'default'"!][!//
                    [!VAR "ChState" = "'biggerThan8'"!][!//
                    [!ELSEIF "$ChState = 'lessThan8'"!][!//
                    [!ERROR!][!//
                    [122-00-03-ERROR]: IcuChannelId ([!"./IcuChannelId"!]) AuxInSource error! All internal routing TOM channel must be in same group, Group1:{TimXChY choose TomXChY (Y < 8)}. group2 {TimXchY choose TomXchY ( Y < 8)  or  choose  Tom(X-1)ChY ( 0 < X , Y < 16) ).
                    [!ENDERROR!][!//
                [!ENDIF!][!//         
             [!ENDIF!][!//         
           

        [!ENDIF!][!//

        [!ENDIF!][!//

    [!ENDIF!]
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!IF "$ChState = 'biggerThan8'"!][!//
  [!VAR "ChState" = "'TRUE'"!][!//
[!ELSE!][!//
  [!VAR "ChState" = "'FALSE'"!][!//
[!ENDIF!][!//  

[!ENDMACRO!][!//
[!ENDINDENT!][!//





[!CALL "CG_FindTotalNumIcuChannelMappedToCorex"!]

[!ENDIF!][!// avoid multiple inclusion ENDIF
[!ENDNOCODE!][!//


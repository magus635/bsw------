/****************************************************************************************************
* 
****************************************************************************************************/
/****************************************************************************************************
*   FileName             : Dio.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : GPIO
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

[!/****************************************************************
    Macro:Dio_CG_GetReadOnlyPorts00to31
    Macro to generate definition to indicate the read only ports of the uC

****************************************************************/!]
[!MACRO "Dio_CG_GetReadOnlyPorts00to31"!][!//
[!NOCODE!][!//
    [!VAR "ReadOnlyPorts" = "num:i(0)"!][!//
    [!FOR "PortNumber" = "0" TO "31"!][!//
        [!IF "contains(ecu:get('Port.AvailableReadOnlyPorts'),concat('_',$PortNumber,'_'))"!][!//
            [!VAR "ReadOnlyPorts" = "bit:bitset($ReadOnlyPorts,$PortNumber)"!][!//
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDNOCODE!][!//
#define DIO_PORTS_READONLY_00_31                 ([!"num:inttohex($ReadOnlyPorts,8)"!]U)
[!ENDMACRO!][!//

[!/************************************************************
    Macro:Dio_CG_GetAvailablePorts00to31
    Macro to generate definition to indicate the ports that are available in the
    microcontroller
    Note:The macro checks for the string Port_AvailablePorts for the ports that are
    available and the corresponding bits within the printed definition are set for 
    all existing ports
****************************************************************/!]
[!MACRO "Dio_CG_GetAvailablePorts00to31"!][!//
[!NOCODE!][!//
    [!VAR "AvailablePorts" = "num:i(0)"!][!//
    [!FOR "PortNumber" = "0" TO "31"!]
        [!IF "(contains(ecu:get('Port.AvailablePortsID'),concat('_',$PortNumber,'_')))"!][!//
            [!VAR "AvailablePorts" = "bit:bitset($AvailablePorts,$PortNumber)"!][!//
        [!ENDIF!]
    [!ENDFOR!]
[!ENDNOCODE!][!//
#define DIO_PORTS_AVAILABLE_00_31      ([!"num:inttohex($AvailablePorts,8)"!]U)
[!ENDMACRO!][!//
[!/************************************************************
    Macro:Dio_CG_GetAvailablePorts32to63
    Macro to generate definition to indicate the ports that are available in the
    microcontroller
    Note:The macro checks for the string Port_AvailablePorts for the ports that are
    available and the corresponding bits within the printed definition are set for 
    all existing ports
****************************************************************/!]
[!MACRO "Dio_CG_GetAvailablePorts32to63"!][!//
[!NOCODE!][!//
    [!VAR "AvailablePorts" = "num:i(0)"!][!//
    [!FOR "PortNumber" = "32" TO "63"!]
        [!IF "(contains(ecu:get('Port.AvailablePortsID'),concat('_',$PortNumber,'_')))"!][!//
            [!VAR "AvailablePorts" = "bit:bitset($AvailablePorts,$PortNumber - 32)"!][!//
        [!ENDIF!]
    [!ENDFOR!]
[!ENDNOCODE!][!//
[!//
#define DIO_PORTS_AVAILABLE_32_63      ([!"num:inttohex($AvailablePorts,8)"!]U)
[!//
[!ENDMACRO!][!//

[!/****************************************************************
    Macro:Dio_CG_GetReadOnlyPorts32to63
    Macro to generate definition to indicate the read only ports of the uC

****************************************************************/!]
[!MACRO "Dio_CG_GetReadOnlyPorts32to63"!][!//
[!NOCODE!][!//
    [!VAR "ReadOnlyPorts" = "num:i(0)"!][!//
    [!FOR "PortNumber" = "32" TO "631"!]
        [!IF "contains(ecu:get('Port.AvailableReadOnlyPorts'),concat('_',$PortNumber,'_'))"!][!//
            [!VAR "ReadOnlyPorts" = "bit:bitset($ReadOnlyPorts,($PortNumber - 32))"!][!//
        [!ENDIF!]
    [!ENDFOR!]
[!ENDNOCODE!][!//
#define DIO_PORTS_READONLY_32_63                 ([!"num:inttohex($ReadOnlyPorts,8)"!]U)
[!ENDMACRO!][!//

[!/*************************************************************
    Macro: Dio_CG_GetAvailablePortPins
    Macro to generate definition to indicate the port pins that are
    available in the microcontroller
***************************************************************/!]
[!MACRO "Dio_CG_GetAvailablePortPins"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!FOR "PortNumber" = "0" TO "num:i(ecu:get('Port.MaxAvailablePortID'))"!][!//
    [!VAR "Port_Temp" = "num:i(0)"!][!//
    [!IF "contains(ecu:get('Port.AvailablePortsID'),concat('_',$PortNumber,'_'))"!][!//
        [!FOR "PinNumber" = "0" TO "num:i(ecu:get('Port.MaxAvailablePinID'))"!][!//
            [!IF "contains(ecu:get(concat('Port.Port',$PortNumber,'_AvailablePins')),concat('_',$PinNumber,'_'))"!][!//
                [!VAR "Port_Temp" = "bit:bitset(num:i($Port_Temp),$PinNumber)"!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
    [!ENDIF!][!//
    #define DIO_AVAILABLE_PINS_PORT[!"$PortNumber"!]                  ([!"num:inttohex($Port_Temp,4)"!]U)
[!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Dio_CG_GetDioChannelSymbolicNames
  Macro to print the symbolic names of each of the Dio channels
*****************************************************************************/!]
[!MACRO "Dio_CG_GetDioChannelSymbolicNames", "PortNumber" = ""!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!FOR "PinNumber" = "0" TO "num:i(ecu:get('Port.MaxAvailablePinID'))"!][!//
        [!VAR "PinId" = "num:i($PortNumber) * num:i(16)"!][!//
        [!VAR "PinId" = "num:i($PinId) + num:i($PinNumber)"!][!//
        [!IF "contains(ecu:get(concat('Port.Port',$PortNumber,'_AvailablePins')),concat('_',$PinNumber,'_'))"!][!//
            [!IF "$PinNumber > num:i(9)"!][!//
                /* #Violation: Dio_Cfg_h_REF_1 */
                #define DIO_CHANNEL_[!"num:i($PortNumber)"!]_[!"num:i($PinNumber)"!]                         ((Dio_ChannelType)[!"num:inttohex($PinId, 3)"!])
            [!ELSE!][!//
                /* #Violation: Dio_Cfg_h_REF_1 */
                #define DIO_CHANNEL_[!"num:i($PortNumber)"!]_[!"num:i($PinNumber)"!]                          ((Dio_ChannelType)[!"num:inttohex($PinId, 3)"!])
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!]
[!/*****************************************************************************
  Macro: Dio_CG_GetDioPortSymbolicNames
  Macro to print the symbolic names of each of the Dio Ports

*****************************************************************************/!]
[!MACRO "Dio_CG_GetDioPortSymbolicNames"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
    [!FOR "PortNumber" = "0" TO "ecu:get('Port.MaxAvailablePortID')"!][!//
        [!IF "contains(ecu:get('Port.AvailablePortsID'),concat('_',$PortNumber,'_'))"!][!//
            [!IF "$PortNumber > num:i(9)"!][!//
                /* #Violation: Dio_Cfg_h_REF_1 */
                #define DIO_PORT_[!"$PortNumber"!]                               ((Dio_PortType)[!"$PortNumber"!])
            [!ELSE!][!//
                /* #Violation: Dio_Cfg_h_REF_1 */
                #define DIO_PORT_[!"$PortNumber"!]                                ((Dio_PortType)[!"$PortNumber"!])
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!]

[!/**********************************************************************
MACRO:CG_GetDioChannelCfgData
Get the Port Pin attributes : Direction, Push-Open control and ALT mode
***********************************************************************/!]
[!MACRO "CG_GetDioChannelCfgData"!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!FOR "PortNumber" = "num:i(0)" TO "ecu:get('Port.MaxAvailablePortID')"!][!//
        [!IF "contains(ecu:get('Port.AvailablePortsID'), concat('_', $PortNumber, '_'))"!][!//
            {/* Port[!"$PortNumber"!] */ [!//
                [!VAR "PortConfigured" = "num:i(0)"!][!//
                [!/* Loop for all DioPort containers to generate configured Port, Channels under this port  */!][!//
                [!IF "node:exists(DioConfig/DioPort/*[DioPortId = num:i($PortNumber)])"!][!//
                    [!SELECT "DioConfig/DioPort/*[DioPortId = num:i($PortNumber)]"!][!//
                        DIO_PORT_CONFIGURED,[!WS "5"!][!//
                        [!FOR "PinNumber" = "0" TO "15"!][!//
                            [!IF "node:exists(DioChannel/*[DioChannelId = num:i($PinNumber)])"!][!//
                                [!VAR "PortConfigured" = "bit:or($PortConfigured,(bit:shl(1,num:i($PinNumber))))"!][!//
                            [!ELSE!][!//
                                [!VAR "PortConfigured" = "bit:or($PortConfigured,(bit:shl(0,num:i($PinNumber))))"!][!//
                            [!ENDIF!][!//
                        [!ENDFOR!][!//
                        ([!"num:inttohex($PortConfigured, 4)"!]U)[!//
                    [!ENDSELECT!][!//
                [!ELSE!][!//
                    DIO_PORT_NOT_CONFIGURED, (0x0000U)[!//
                [!ENDIF!][!//
            }[!IF "$PortNumber != ecu:get('Port.MaxAvailablePortID')"!],[!ENDIF!]
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*************************************************************
    Macro: CG_GetAvailablePortIndex
    Macro to generate definition to extract the port index
***************************************************************/!]
[!MACRO "CG_GetAvailablePortIndex"!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!VAR "PortCount" = "num:i(0)"!][!//
    [!FOR "PortNumber" = "0" TO "num:i(ecu:get('Port.MaxAvailablePortID'))"!][!//
        [!IF "contains(ecu:get('Port.AvailablePortsID'),concat('_',$PortNumber,'_'))"!][!//
            0x[!"substring-after(text:toupper(num:inttohex($PortCount, 2)), 'X')"!]U[!IF "$PortNumber != ecu:get('Port.MaxAvailablePortID')"!],[!ELSE!][!WS!][!ENDIF!]   /* Port[!"$PortNumber"!] */
            [!VAR "PortCount" = "num:i($PortCount) + num:i(1)"!][!//
        [!ELSE!][!//
            0xFFU[!IF "$PortNumber != ecu:get('Port.MaxAvailablePortID')"!],[!ELSE!][!WS!][!ENDIF!]   /* Port[!"$PortNumber"!] */
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*************************************************************
    Macro: CG_GetAvailablePortPins
    Macro to generate definition to indicate the port pins that are
    available in the microcontroller
***************************************************************/!]
[!MACRO "CG_GetAvailablePortPins"!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!FOR "PortNumber" = "0" TO "num:i(ecu:get('Port.MaxAvailablePortID'))"!][!//
        [!IF "contains(ecu:get('Port.AvailablePortsID'),concat('_',$PortNumber,'_'))"!][!//
            [!VAR "Port_Temp" = "num:i(0)"!][!//
            [!FOR "PinNumber" = "0" TO "num:i(ecu:get('Port.MaxAvailablePinID'))"!][!//
                [!IF "contains(ecu:get(concat('Port.Port',$PortNumber,'_AvailablePins')),concat('_',$PinNumber,'_'))"!][!//
                    [!VAR "Port_Temp" = "bit:bitset(num:i($Port_Temp),$PinNumber)"!][!//
                [!ENDIF!][!//
            [!ENDFOR!][!//
                [!"num:inttohex($Port_Temp,4)"!]U[!IF "$PortNumber != ecu:get('Port.MaxAvailablePortID')"!],[!ELSE!][!WS!][!ENDIF!]    /* Port[!"$PortNumber"!] */
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: Dio_CG_GetDioChannelGroupDefinition

  Macro to set the definition of the channel group under each
  Port.

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "Dio_CG_GetDioChannelGroupDefinition"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!/* If there are DIO channel groups configured */!][!//
[!IF "num:i(count(DioConfig/DioPort/*/DioChannelGroup/*)) > 0"!][!//
    [!INDENT "4"!][!//
    [!/* Variables used in this configuration structure */!][!//
    [!VAR "PortName" = "0"!][!//
    [!VAR "PortId" = "0"!][!//
    [!VAR "PortOffset" = "0"!][!//
    [!VAR "BitPosition" = "0"!][!//
    [!VAR "Counter" = "0"!][!//
    [!VAR "GroupCount" = "num:i(count(DioConfig/DioPort/*/DioChannelGroup/*))"!][!//
    [!/* Loop for all DioPort containers */!][!//
    [!LOOP "DioConfig/DioPort/*"!][!//
        [!VAR "PortName" = "node:name(.)"!][!//
        [!VAR "PortId" = "num:i(./DioPortId)"!][!//
        [!LOOP "./DioChannelGroup/*"!][!//
            [!/* To skip the first comma in the generated file */!][!//
            [!/* Calculate the offset depending on the value of the DioPortMask */!][!//
            [!VAR "PortOffset" = "num:i(0)"!][!//
            [!FOR "BitPosition" = "num:i(0)" TO "num:i(15)"!][!//
                [!IF "bit:getbit( num:i(DioPortMask), num:i($BitPosition) ) = 'true'"!][!//
                [!VAR "PortOffset" = "num:i($BitPosition)"!][!//
                [!BREAK!][!//
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!VAR "Counter" = "$Counter + num:i(1)"!][!//
            {
                [!INDENT "8"!][!//
                /* [!"$PortName"!], [!"DioChannelGroupIdentification"!] */
                (Dio_PortType)[!"num:i($PortId)"!]U,          /* Port Id */
                (uint8)[!"num:i($PortOffset)"!]U,                  /* Offset  */
                (Dio_PortLevelType)[!"num:inttohex(num:i(DioPortMask))"!]U    /* Mask    */
                [!ENDINDENT!][!//
            }[!IF "num:i($Counter) != $GroupCount"!],[!ELSE!][!WS!][!ENDIF!]
        [!ENDLOOP!][!/*LOOP "./DioChannelGroup/*"*/!][!//
    [!ENDLOOP!][!/*LOOP "DioPort/*"*/!][!//
    [!ENDINDENT!][!//
    [!/* If there are no DIO channel groups configured */!][!//
[!ELSE!][!//
    /* No Groups are configured */
[!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  Macro: CG_GetUserDefinedSymbolicNames

  Macro to print the user defined symbolic names of each Dio Port/Channel/Group

  Input Parameters:
  None
*****************************************************************************/!]
[!MACRO "CG_GetUserDefinedSymbolicNames"!][!//
[!//
[!CODE!][!//
[!INDENT "0"!][!//
[!/* Variable used as index to refer to the channel groups */!][!//
[!VAR "DioChannelIndex" = "num:i(0)"!][!//
[!//
[!/* Loop for all DioPort containers to generate symbolic names for the Port,
     Channels under this port & Channel groups under this port */!][!//
[!LOOP "DioConfig/DioPort/*"!][!//

    [!VAR "PortId" = "num:i(./DioPortId)"!][!//
    [!VAR "PortName" = "concat('DIO_PORT_', num:i(./DioPortId))"!][!//
    [!VAR "ChannelPrefix" = "concat('DIO_CHANNEL_', num:i(./DioPortId))"!][!//
    [!VAR "ChannelGroupPrefix" = "'Dio_kChannelGroupConfig'"!][!//
    [!VAR "PortSymbolicName" = "node:name(.)"!][!//
    /*
    DIO PORT : ([!"$PortSymbolicName"!])
    */
    [!VAR "PortSymbolicName" = "normalize-space($PortSymbolicName)"!][!//
    [!IF "num:i(string-length($PortSymbolicName)) != 0"!][!//
    
        /* To prevent double declaration */
        #ifndef DioConf_DioPort_[!"$PortSymbolicName"!]
        #define DioConf_DioPort_[!"$PortSymbolicName"!]                                 ([!"$PortName"!])
        #endif
    [!ENDIF!][!//
    [!/* Generate Symbolic names for Dio channels under this port */!][!//
    [!LOOP "./DioChannel/*"!][!//
        [!VAR "ChannelName" = "concat($ChannelPrefix,'_', num:i(./DioChannelId))"!][!//
        [!VAR "ChannelSymbolicName" = "node:name(.)"!][!//
        [!VAR "ChannelSymbolicName" = "normalize-space($ChannelSymbolicName)"!][!//
        /* DIO Channel : ([!"$ChannelSymbolicName"!]) */
        [!IF "num:i(string-length($ChannelSymbolicName)) != 0"!][!//
            /* To prevent double declaration */
            #ifndef DioConf_DioChannel_[!"$ChannelSymbolicName"!]
            #define DioConf_DioChannel_[!"$ChannelSymbolicName"!]                             ([!"$ChannelName"!])
            #endif
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!/* Generate Symbolic names for Dio channel groups under this port */!][!//
    [!LOOP "./DioChannelGroup/*"!][!//
        [!VAR "ChannelGroupSymbolicName" = "DioChannelGroupIdentification"!][!//
        [!VAR "ChannelGroupSymbolicName" = "normalize-space($ChannelGroupSymbolicName)"!][!//
        /*DIO Channel Group : [!"$ChannelGroupSymbolicName"!]*/
        [!IF "num:i(string-length($ChannelGroupSymbolicName)) != num:i(0)"!][!//
            /* To prevent double declaration */
            #ifndef DioConf_DioChannelGroup_[!"$ChannelGroupSymbolicName"!]
            #define DioConf_DioChannelGroup_[!"$ChannelGroupSymbolicName"!]                        (&Dio_ConfigSet.Dio_ChGroupDataPtr[[!"num:i($DioChannelIndex)"!]])
            #endif
        [!ENDIF!][!//
    [!VAR "DioChannelIndex" = "$DioChannelIndex + 1"!][!//
    [!ENDLOOP!][!/* LOOP "./DioChannelGroup/*" */!][!//
[!ENDLOOP!][!/*LOOP "DioPort/*"*/!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//
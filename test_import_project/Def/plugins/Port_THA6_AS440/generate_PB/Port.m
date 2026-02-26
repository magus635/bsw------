[!/*************************************************************
    Macro: CG_GetPortPinRXMUXSymbolicName
    Macro to generate corresponding to the Port-Pin Symbolic name
***************************************************************/!]
[!MACRO "CG_GetPortPinRXMUXSymbolicName"!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "0"!][!//
/* Generate IOM input multiplexing register configuration values */
[!FOR "Counter" = "0" TO "2"!][!//
    [!FOR "PortNumber" = "num:i(0)" TO "num:i(ecu:get('Port.MaxAvailablePortID'))"!][!//
        [!IF "contains(ecu:get('Port.AvailablePortsID'),concat('_',$PortNumber,'_'))"!][!//
            [!FOR "PinNumber" = "0" TO "15"!][!//
                    [!VAR "RXMUX_IOMMON" = "concat('Port.RXMUX_IOMMON',$Counter,'_',$PortNumber,'_',$PinNumber)"!][!//
                    [!IF "ecu:has($RXMUX_IOMMON)"!][!//
                        [!VAR "RXMUX_IOMMON_VAR" = "ecu:get($RXMUX_IOMMON)"!][!//
                        /* #Violation: Port_Cfg_h_REF_1 */
                        #define PORT_RXMUX_IOMMON[!"$Counter"!]_[!"$PortNumber"!]_[!"$PinNumber"!]        [!IF "$PortNumber < num:i(10)"!][!WS!][!ENDIF!][!IF "$PinNumber < num:i(10)"!][!WS!][!ENDIF!][!"$RXMUX_IOMMON_VAR"!]
                    [!ENDIF!][!//
            [!ENDFOR!][!//
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDFOR!][!//
[!//
[!IF "contains(as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative, 'THA610X')"!][!//
    /* Generate GTM input multiplexing register configuration values */
    [!FOR "PortNumber" = "num:i(0)" TO "num:i(ecu:get('Port.MaxAvailablePortID'))"!][!//
        [!IF "contains(ecu:get('Port.AvailablePortsID'),concat('_',$PortNumber,'_'))"!][!//
            [!FOR "PinNumber" = "0" TO "15"!][!//
                [!FOR "Counter" = "0" TO "7"!][!//
                    [!VAR "RXMUX_GTM" = "concat('Port.RXMUX_GTMTIO',$Counter, '_', $PortNumber,'_',$PinNumber)"!][!//
                    [!IF "ecu:has($RXMUX_GTM)"!][!//
                        [!VAR "RXMUX_GTM_VAR" = "ecu:get($RXMUX_GTM)"!][!//
                        /* #Violation: Port_Cfg_h_REF_1 */
                        #define PORT_RXMUX_GTMTIO[!"$Counter"!]_[!"$PortNumber"!]_[!"$PinNumber"!]        [!IF "$PortNumber < num:i(10)"!][!WS!][!ENDIF!][!IF "$PinNumber < num:i(10)"!][!WS!][!ENDIF!][!"$RXMUX_GTM_VAR"!]
                    [!ENDIF!][!//
                [!ENDFOR!][!//
            [!ENDFOR!][!//
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!IF "contains(as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative, 'THA610X')"!][!//
    /* Generate EXTI input multiplexing register configuration values */
    [!FOR "PortNumber" = "num:i(0)" TO "num:i(ecu:get('Port.MaxAvailablePortID'))"!][!//
        [!IF "contains(ecu:get('Port.AvailablePortsID'),concat('_',$PortNumber,'_'))"!][!//
            [!FOR "PinNumber" = "0" TO "15"!][!//
                [!FOR "Counter" = "0" TO "7"!][!//
                    [!FOR "Node" = "0" TO "3"!][!//
                        [!VAR "RXMUX_EXTI" = "concat('Port.RXMUX_EXTIREQ', $Counter, $Node, 'SEL_', $PortNumber,'_',$PinNumber)"!][!//
                        [!IF "ecu:has($RXMUX_EXTI)"!][!//
                            [!VAR "RXMUX_EXTI_VAR" = "ecu:get($RXMUX_EXTI)"!][!//
                            /* #Violation: Port_Cfg_h_REF_1 */
                            #define PORT_RXMUX_EXTIREQ[!"$Counter"!][!"$Node"!]_[!"$PortNumber"!]_[!"$PinNumber"!]      [!IF "$PortNumber < num:i(10)"!][!WS!][!ENDIF!][!IF "$PinNumber < num:i(10)"!][!WS!][!ENDIF!][!"$RXMUX_EXTI_VAR"!]
                        [!ENDIF!][!//
                    [!ENDFOR!][!//
                [!ENDFOR!][!//
            [!ENDFOR!][!//
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!IF "contains(as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative, 'THA610X')"!][!//
    /* Generate IOMPIN input multiplexing register configuration values */
    [!FOR "Node" = "0" TO "15"!][!//
        [!FOR "PortNumber" = "num:i(0)" TO "num:i(ecu:get('Port.MaxAvailablePortID'))"!][!//
            [!IF "contains(ecu:get('Port.AvailablePortsID'),concat('_',$PortNumber,'_'))"!][!//
                [!FOR "PinNumber" = "0" TO "15"!][!//
                    [!VAR "RXMUX_IOMPIN" = "concat('Port.RXMUX_IOMPIN', $Node, '_', $PortNumber, '_', $PinNumber)"!][!//
                    [!IF "ecu:has($RXMUX_IOMPIN)"!][!//
                        [!VAR "RXMUX_IOMPIN_VAR" = "ecu:get($RXMUX_IOMPIN)"!][!//
                        /* #Violation: Port_Cfg_h_REF_1 */
                        #define PORT_RXMUX_IOMPIN[!"$Node"!]_[!"$PortNumber"!]_[!"$PinNumber"!]       [!IF "$PortNumber < num:i(10)"!][!WS!][!ENDIF!][!IF "$PinNumber < num:i(10)"!][!WS!][!ENDIF!][!"$RXMUX_IOMPIN_VAR"!]
                    [!ENDIF!][!//
                [!ENDFOR!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
    [!ENDFOR!][!//
[!ENDIF!][!//
[!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//


[!/*************************************************************
    Macro: CG_GetPortPinSymbolicName
    Macro to generate corresponding to the Port-Pin Symbolic name
***************************************************************/!]
[!MACRO "CG_GetPortPinSymbolicName"!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "0"!][!//
    /*  SWS_Port_00006:
        [!WS "4"!]The user of the PORT Driver module shall configure the symbolic names of the port pins of the MCU.
        [!WS "4"!]SWS_Port_00207:
        [!WS "4"!]These symbolic names for the individual port pins (e.g. PORT_A_PIN_0)
        [!WS "4"!]shall be defined in the configuration tool.
        [!WS "4"!]SWS_Port_00076:
        [!WS "4"!]The PORT Driver module's implementer shall define symbolic names in the file Port_Cfg.h
    */
    [!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
        [!VAR "PortNumber" = "./PortNumber"!][!//
        [!VAR "PortContainer" = "node:name(.)"!][!//
        /* Symbolic Name: Port[!"$PortNumber"!] */
        #ifndef PortConf_[!"$PortContainer"!]
        #define PortConf_[!"$PortContainer"!][!WS "20"!]([!"$PortNumber"!]U)
        /* #Violation: Port_Cfg_h_REF_1 */
        #define PortConf_PORT_[!"$PortNumber"!][!WS "29"!]([!"$PortNumber"!]U)
        #endif
        [!LOOP "node:order(./PortPin/*, 'PortPinId')"!][!//
            [!VAR "PinNumber" = "text:split(node:value(./PortPinSymbolicName),'.')[last()]"!][!//
            [!IF "(contains(ecu:get(concat('Port.Port',$PortNumber,'_AvailablePins')),concat('_',$PinNumber,'_')))"!][!//
                /* Symbolic Name: P[!"$PortNumber"!].[!"$PinNumber"!]
                    The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
                #ifndef PortConf_[!"$PortContainer"!]_[!"node:name(.)"!]
                #define PortConf_[!"$PortContainer"!]_[!"node:name(.)"!][!WS "10"!]((Port_PinType) [!"num:inttohex(bit:or(bit:shl($PortNumber, 4),$PinNumber),3)"!]U)
                /* #Violation: Port_Cfg_h_REF_1 */
                #define PortConf_[!"$PortContainer"!]_PORT_[!"$PortNumber"!]_PIN_[!"$PinNumber"!][!WS "7"!]((Port_PinType) [!"num:inttohex(bit:or(bit:shl($PortNumber, 4),$PinNumber),3)"!]U)
                #endif
                [!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: Port_PinAttributesCheck
  Get the result of checking the properties of Port-Pin.
  NotRO   : Check that the Port-Pin is not read-only
            true:        Check the current properties of the Port-Pin
            false: Don't check the current properties of the Port-Pin
  NotDir  : Check the Port-Pin direction is not "NotDir"
            PORT_PIN_IN
            PORT_PIN_OUT
            PORT_PIN_INOUT: Directions that can be checked
            false:          Don't check the current properties of the Port-Pin
  NotAI   : Check the analog input(AI) function is disabled on the current Port-Pin
            true:        Check the current properties of the Port-Pin
            false: Don't check the current properties of the Port-Pin
  NotO    : Check the peripheral control(0) function is disabled on the current Port-Pin
            true:        Check the current properties of the Port-Pin
            false: Don't check the current properties of the Port-Pin
  RxMux: Check the Port-Pin input multiplexing function is disabled on the current Port-Pin
         true:        Check the current properties of the Port-Pin
         false: Don't check the current properties of the Port-Pin
*****************************************************************************/!]
[!MACRO "Port_PinAttributesCheck", "NotRO" = "", "NotDir" = "", "NotAI" = "", "NotO" = "", "RxMux" = ""!][!//
[!//
[!NOCODE!][!//
[!VAR "CheckResult" = "'false'"!]
[!IF "./PortPinEnable = 'true'"!][!//

    [!/* Check that the Port-Pin is not read-only;  $NotRO = 'false': Skip Check */!]
    [!IF "$NotRO = 'false' or not(./PortPinDirection != 'PORT_PIN_OUT' and contains(ecu:get('Port.AvailableReadOnlyPorts'), concat('_',../../PortNumber,'_')))"!][!//

        [!/* Check the Port-Pin direction is not "NotDir";  $NotDir = 'false': Skip Check */!]
        [!IF "$NotDir = 'false' or not(./PortPinDirection = $NotDir and ./PortPinDirectionChangeable = 'false')"!][!//

            [!/* Check the analog input(AI) function is disabled on the current Port-Pin;  $NotAI = 'false': Skip Check */!]
            [!IF "$NotAI = 'false' or ./PortPinAnalogInputEnable = 'false'"!][!//

                [!/* Check the peripheral control(0) function is disabled on the current Port-Pin;  $NotO = 'false': Skip Check */!]
                [!IF "$NotO = 'false' or not(./PortPinDirection != 'PORT_PIN_IN' and contains(ecu:get('Port.AvailabletPeripheralAltMode'), concat(./PortPinInitialMode, ' ')))"!][!//

                    [!/* Check the Port-Pin input multiplexing function is disabled on the current Port-Pin;  $RxMux = 'false': Skip Check */!]
                    [!VAR "CheckString" = "substring(./RxMuxFunSelect, 1, num:i(string-length(./RxMuxFunSelect) - 1))"!]
                    [!IF "$RxMux = 'true'
                        and ./PortPinDirection != 'PORT_PIN_OUT'
                        and ./RxMuxFunSelect != 'GPIO'
                        and  not(contains(ecu:get('Port.RxMuxNotCheck'), concat('_', text:split(./RxMuxFunSelect, '_')[1], '_')))
                        and  not(contains(ecu:get('Port.RxMuxNotCheck'), concat('_', $CheckString, '_')))
                        and contains($ALLPortPinInputConfig, $CheckString)"!][!//
                        [!VAR "PortPin1" = "substring-after(substring-before(substring-after($ALLPortPinInputConfig,$CheckString),'; '),':')"!][!//
                        [!VAR "PortPin2" = "concat('P',../../PortNumber, '.', num:i(./PortPinId - ../../PortNumber * 16))"!][!//
                        [!ERROR!][!//
                            124-00-09-ERROR: Invalid 'RxMuxFunSelect', [!"$PortPin1"!] and [!"$PortPin2"!] use the same input multiplexing function: [!"$CheckString"!]x!][!//
                        [!ENDERROR!][!//
                    [!/* All previous inspections passed and the port pin input multiplexing function is not configured repeatedly*/!]
                    [!ELSE!][!//
                        [!VAR "CheckResult" = "'true'"!]
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: Port_GetInputOutputConfig
  Get Port Config message to var
*****************************************************************************/!]
[!MACRO "Port_GetInputOutputConfig"!][!//
[!//
[!NOCODE!][!//
[!VAR "ALLPortPinOutputConfig" = "''"!]  [!/* Define a variable to save all the 'PortPinInitialMode' strings */!][!//
[!VAR "ALLPortPinInputConfig" = "''"!]   [!/* Define a variable to save all the 'RxMuxFunSelect' strings */!][!//
[!VAR "RxMuxCount" = "num:i(0)"!]        [!/* Define a variable to count the number of 'RXMUX' registers */!][!//
[!FOR "PortNumber" = "0" TO "num:i(ecu:get('Port.MaxAvailablePortID'))"!][!//
    [!FOR "PinNumber" = "0" TO "num:i(ecu:get('Port.MaxAvailablePinID'))"!][!//
        [!VAR "PortPinID" = "num:i($PortNumber * 16 + $PinNumber)"!][!//
        [!IF "node:exists(PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PortPinID)])"!][!//
            [!SELECT "PortConfigSet/PortContainer/*/PortPin/*[PortPinId = num:i($PortPinID)]"!][!//
                [!CALL "Port_PinAttributesCheck", "NotRO" = "'true'", "NotDir" = "'PORT_PIN_IN'", "NotAI" = "'true'", "NotO" = "'true'", "RxMux" = "'false'"!][!//
                [!IF "$CheckResult = 'true'"!][!//
                    [!VAR "ALLPortPinOutputConfig" = "concat($ALLPortPinOutputConfig, ./PortPinInitialMode,':P', $PortNumber,'.',$PinNumber,'; ')"!][!//
                [!ENDIF!][!//
                
                [!CALL "Port_PinAttributesCheck", "NotRO" = "'false'", "NotDir" = "'PORT_PIN_OUT'", "NotAI" = "'true'", "NotO" = "'false'", "RxMux" = "'true'"!][!//
                [!IF "$CheckResult = 'true'"!][!//
                    [!VAR "ALLPortPinInputConfig" = "concat($ALLPortPinInputConfig, ./RxMuxFunSelect, ':P',$PortNumber,'.',$PinNumber,'; ')"!][!//
                [!ENDIF!][!//
            [!ENDSELECT!][!//
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*************************************************************
    Macro: CG_GetRxMuxTotalNum
    Macro to generate corresponding to the Port-Pin Symbolic name
***************************************************************/!]
[!MACRO "CG_GetRxMuxTotalNum"!][!//
[!//
[!NOCODE!][!//
[!AUTOSPACING!][!//
[!INDENT "0"!][!//
[!VAR "RxMuxTotalNum" = "num:i(0)"!][!//
    [!FOR "Count" = "num:i(0)" TO "count(text:split(ecu:get('Port.AvailableCANModule'), '_'))"!][!//
        [!VAR "RxMuxTotalNum" = "num:i($RxMuxTotalNum + text:split(ecu:get('Port.AvailableCANModule'), '_')[position() -1 = num:i($Count)])"!][!//
    [!ENDFOR!][!//

    [!IF "not(contains(as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative, 'THA610X'))"!][!//
        [!FOR "Count" = "0" TO "count(text:split(ecu:get('Port.AvailableDSADCModule'), '_'))"!][!//
            [!VAR "RxMuxTotalNum" = "num:i($RxMuxTotalNum + text:split(ecu:get('Port.AvailableDSADCModule'), '_')[position() -1 = num:i($Count)])"!][!//
        [!ENDFOR!][!//
    [!ENDIF!][!//

    [!FOR "Count" = "0" TO "count(text:split(ecu:get('Port.AvailableETHModule'), '_'))"!][!//
        [!VAR "RxMuxTotalNum" = "num:i($RxMuxTotalNum + text:split(ecu:get('Port.AvailableETHModule'), '_')[position() -1 = num:i($Count)])"!][!//
    [!ENDFOR!][!//

    [!FOR "Count" = "0" TO "count(text:split(ecu:get('Port.AvailableI2CModule'), '_'))"!][!//
        [!VAR "RxMuxTotalNum" = "num:i($RxMuxTotalNum + text:split(ecu:get('Port.AvailableI2CModule'), '_')[position() -1 = num:i($Count)])"!][!//
    [!ENDFOR!][!//

    [!FOR "Count" = "0" TO "count(text:split(ecu:get('Port.AvailableASIModule'), '_'))"!][!//
        [!VAR "RxMuxTotalNum" = "num:i($RxMuxTotalNum + text:split(ecu:get('Port.AvailableASIModule'), '_')[position() -1 = num:i($Count)])"!][!//
    [!ENDFOR!][!//

    [!FOR "Count" = "0" TO "count(text:split(ecu:get('Port.AvailableESPIModule'), '_'))"!][!//
        [!VAR "RxMuxTotalNum" = "num:i($RxMuxTotalNum + text:split(ecu:get('Port.AvailableESPIModule'), '_')[position() -1 = num:i($Count)])"!][!//
    [!ENDFOR!][!//

    [!FOR "Count" = "0" TO "count(text:split(ecu:get('Port.AvailableSENTModule'), '_'))"!][!//
        [!VAR "RxMuxTotalNum" = "num:i($RxMuxTotalNum + text:split(ecu:get('Port.AvailableSENTModule'), '_')[position() -1 = num:i($Count)])"!][!//
    [!ENDFOR!][!//

    [!FOR "Count" = "0" TO "count(text:split(ecu:get('Port.AvailableIOMMONModule'), '_'))"!][!//
        [!VAR "RxMuxTotalNum" = "num:i($RxMuxTotalNum + text:split(ecu:get('Port.AvailableIOMMONModule'), '_')[position() -1 = num:i($Count)])"!][!//
    [!ENDFOR!][!//

    [!FOR "Count" = "0" TO "count(text:split(ecu:get('Port.AvailableDBGModule'), '_'))"!][!//
        [!VAR "RxMuxTotalNum" = "num:i($RxMuxTotalNum + text:split(ecu:get('Port.AvailableDBGModule'), '_')[position() -1 = num:i($Count)])"!][!//
    [!ENDFOR!][!//

    [!IF "contains(as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative, 'THA6412')"!][!//
        [!FOR "Count" = "0" TO "count(text:split(ecu:get('Port.AvailablePSI5Module'), '_'))"!][!//
            [!VAR "RxMuxTotalNum" = "num:i($RxMuxTotalNum + text:split(ecu:get('Port.AvailablePSI5Module'), '_')[position() -1 = num:i($Count)])"!][!//
        [!ENDFOR!][!//
    [!ENDIF!][!//

    [!IF "contains(as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative, 'THA610X')"!][!//
        [!FOR "Count" = "0" TO "count(text:split(ecu:get('Port.AvailableIOMPINModule'), '_'))"!][!//
            [!VAR "RxMuxTotalNum" = "num:i($RxMuxTotalNum + text:split(ecu:get('Port.AvailableIOMPINModule'), '_')[position() -1 = num:i($Count)])"!][!//
        [!ENDFOR!][!//

        [!FOR "Count" = "0" TO "count(text:split(ecu:get('Port.AvailableGTMModule'), '_'))"!][!//
            [!VAR "RxMuxTotalNum" = "num:i($RxMuxTotalNum + text:split(ecu:get('Port.AvailableGTMModule'), '_')[position() -1 = num:i($Count)])"!][!//
        [!ENDFOR!][!//

        [!FOR "Count" = "0" TO "count(text:split(ecu:get('Port.AvailableEXTIModule'), '_'))"!][!//
            [!VAR "RxMuxTotalNum" = "num:i($RxMuxTotalNum + text:split(ecu:get('Port.AvailableEXTIModule'), '_')[position() -1 = num:i($Count)])"!][!//
        [!ENDFOR!][!//
    
        [!VAR "RxMuxTotalNum" = "num:i($RxMuxTotalNum + 11)"!][!//
    [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!CALL "CG_GetRxMuxTotalNum"!][!//
[!/**********************************************************************
MACRO:CG_GetPortPinDirectionAndModeAttributes_CTRx
Get the Port Pin attributes : Direction, Push-Open control and ALT mode
***********************************************************************/!]
[!MACRO "CG_GetPortPinDirectionAndModeAttributes_CTRx"!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!VAR "AvailablePortTotalNumber" = "ecu:get('Port.AvailablePortsTotalNumber')"!][!//
    [!VAR "PortCount" = "0"!][!//
    [!VAR "OutPinAltMode"="ecu:get('Port.Pin_AvaliabeleMode')"!][!//
    [!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
    {
        [!INDENT "8"!][!//
        {
            [!VAR "PortCount" = "num:i($PortCount + 1)"!][!//
            [!VAR "PorNumber" = "./PortNumber"!][!//
            [!INDENT "12"!][!//
            {
                [!INDENT "16"!][!//
                /*        Port[!"./PortNumber"!]: Pn_CTR        */
                [!FOR "PinNumber" = "0" TO "ecu:get('Port.MaxAvailablePinID')"!][!//
                    [!VAR "PortPinIdNumber" = "num:i($PorNumber * 16 + $PinNumber)"!][!//
                    [!IF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber]) and (./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'true'"!][!//
                        [!SELECT "./PortPin/*[PortPinId = $PortPinIdNumber]"!][!//
                        [!IF "(./PortPinId = 512 or ./PortPinId = 513 or ./PortPinId = 515) and node:containsValue(as:modconf('Resource')/ResourceGeneral/ResourceSubderivative, 'THA6412_BGA516')"!][!//
                            [!WARNING!][!//
                                [124-00-10-WARNING]: If the THA6412 is powered internally, it is not allowed to configure the current Port-Pin([!"./PortPinSymbolicName"!]) for digital function.
                            [!ENDWARNING!][!//
                        [!ENDIF!][!//
                        [!IF "./PortPinAnalogInputEnable = 'true' or ./PortPinDirection = 'PORT_PIN_IN'"!][!//
                            (uint8)(PORT_PIN_IN)[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "61"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                        [!ELSEIF "./PortPinDirection != 'PORT_PIN_IN' and
                                  contains(ecu:get('Port.AvailabletPeripheralAltMode'), concat(./PortPinInitialMode, ' '))"!][!//
                            ((uint8)[!"PortPinDirection"!] | (uint8)[!"PortPinOutputPushMode"!])[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "28"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                        [!ELSE!][!//
                            [!VAR "MacPinMode"="concat(./PortPinInitialMode,'_',num:inttohex(num:i(PortPinId),4))"!][!//
                            [!VAR "OutPutMode"="substring-after(substring-before((substring-after($OutPinAltMode,$MacPinMode)),':'),';')"!][!//
                            ((uint8)[!"PortPinDirection"!] | (uint8)[!"PortPinOutputPushMode"!] | (uint8)[!"$OutPutMode"!])[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "3"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                        [!ENDIF!][!//
                        [!ENDSELECT!][!//
                    [!ELSEIF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber]) and (./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'false'"!][!//
                            ((uint8)PORT_PIN_NOTENABLE)[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "54"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ELSE!][!//
                        ((uint8)PORT_PIN_UNSUPPORT)[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "54"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ENDIF!][!//
                [!ENDFOR!][!//
                [!ENDINDENT!][!//
            }
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }[!IF "num:i($PortCount) != num:i($AvailablePortTotalNumber)"!],[!ENDIF!]
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//
[!/**********************************************************************
MACRO:CG_GetPortPinOutputVoltageLevel_ODR
Get the Port Pin attributes : output voltage level
***********************************************************************/!]
[!MACRO "CG_GetPortPinOutputVoltageLevel_ODR", "Port" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!VAR "AvailablePortTotalNumber" = "ecu:get('Port.AvailablePortsTotalNumber')"!][!//
    [!VAR "PortCount" = "0"!][!//
    [!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
    {
        [!VAR "PortCount" = "num:i($PortCount + 1)"!][!//
        [!VAR "PorNumber" = "./PortNumber"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*          Port[!"./PortNumber"!]: Pn_ODR          */
            [!FOR "PinNumber" = "0" TO "ecu:get('Port.MaxAvailablePinID')"!][!//
                [!VAR "PortPinIdNumber" = "num:i($PorNumber * 16 + $PinNumber)"!][!//
                [!IF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber]) and (./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'true'"!][!//
                    [!SELECT "./PortPin/*[PortPinId = $PortPinIdNumber]"!][!//
                    [!CALL "Port_PinAttributesCheck", "NotRO" = "'true'", "NotDir" = "'PORT_PIN_IN'", "NotAI" = "'true'", "NotO" = "'false'", "RxMux" = "'false'"!][!//
                    [!IF "$CheckResult = 'true'"!][!//
                        (uint8)[!"./PortPinLevelValue"!],[!WS "11"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ELSE!][!//
                        (uint8)PORT_PIN_LEVEL_LOW,[!WS "11"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ENDIF!][!//
                    [!ENDSELECT!][!//
                [!ELSEIF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber]) and (./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'false'"!][!//
                    (uint8)PORT_PIN_NOTENABLE,[!WS "11"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                [!ELSE!][!//
                    (uint8)PORT_PIN_UNSUPPORT,[!WS "11"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                [!ENDIF!][!//
            [!ENDFOR!][!//
                (uint16)PORT_RXRESERVE[!WS "15"!]/* RXRESERVE */
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }[!IF "num:i($PortCount) != num:i($AvailablePortTotalNumber)"!],[!ENDIF!]
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//
[!/**********************************************************************
MACRO:CG_GetPortPinOutputVoltageLevel_STTL
Get the Port Pin attributes : TTL level working mode
***********************************************************************/!]
[!MACRO "CG_GetPortPinOutputVoltageLevel_STTL", "Port" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!VAR "AvailablePortTotalNumber" = "ecu:get('Port.AvailablePortsTotalNumber')"!][!//
    [!VAR "PortCount" = "0"!][!//
    [!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
    {
        [!VAR "PortCount" = "num:i($PortCount + 1)"!][!//
        [!VAR "PorNumber" = "./PortNumber"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*          Port[!"./PortNumber"!]: Pn_STTL          */
            [!FOR "PinNumber" = "0" TO "ecu:get('Port.MaxAvailablePinID')"!][!//
                [!VAR "PortPinIdNumber" = "num:i($PorNumber * 16 + $PinNumber)"!][!//
                [!IF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber]) and (./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'true'"!][!//
                    [!SELECT "./PortPin/*[PortPinId = $PortPinIdNumber]"!][!//
                    [!CALL "Port_PinAttributesCheck", "NotRO" = "'false'", "NotDir" = "'PORT_PIN_OUT'", "NotAI" = "'true'", "NotO" = "'false'", "RxMux" = "'false'"!][!//
                    [!IF "$CheckResult = 'true' and
                          ./PortPinPadTriggerMode = 'PORT_SCHMIDT_LEVEL_MODE' and
                          ./PortPinPadLevel = 'PORT_PDR_STTL_AUTOMOTIVE_LEVEL'"!][!//
                        (uint8)PORT_PDR_STTL_AUTOMOTIVE_LEVEL,[!WS "11"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ELSE!][!//
                        (uint8)PORT_PDR_DTTL_AUTOMOTIVE_LEVEL,[!WS "11"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ENDIF!][!//
                    [!ENDSELECT!][!//
                [!ELSEIF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber]) and (./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'false'"!][!//
                    (uint8)PORT_PIN_NOTENABLE,[!WS "23"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                [!ELSE!][!//
                    (uint8)PORT_PIN_UNSUPPORT,[!WS "23"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                [!ENDIF!][!//
            [!ENDFOR!][!//
                (uint16)PORT_RXRESERVE[!WS "27"!]/* RXRESERVE */
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }[!IF "num:i($PortCount) != num:i($AvailablePortTotalNumber)"!],[!ENDIF!]
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//
[!/**********************************************************************
MACRO:CG_GetPortPinDriverLevelAndStrength_DSRx
Get the Port Pin attributes : Pad level and pad strength
***********************************************************************/!]
[!MACRO "CG_GetPortPinDriverLevelAndStrength_DSRx", "Port" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!VAR "AvailablePortTotalNumber" = "ecu:get('Port.AvailablePortsTotalNumber')"!][!//
    [!VAR "PortCount" = "0"!][!//
    [!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
    {
        [!VAR "PortCount" = "num:i($PortCount + 1)"!][!//
        [!VAR "PorNumber" = "./PortNumber"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
             /*          Port[!"./PortNumber"!]: Pn_DSR          */
            [!FOR "PinNumber" = "0" TO "ecu:get('Port.MaxAvailablePinID')"!][!//
                [!VAR "PortPinIdNumber" = "num:i($PorNumber * 16 + $PinNumber)"!][!//
                [!IF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber]) and (./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'true'"!][!//
                    [!SELECT "./PortPin/*[PortPinId = $PortPinIdNumber]"!][!//
                    [!CALL "Port_PinAttributesCheck", "NotRO" = "'false'", "NotDir" = "'PORT_PIN_OUT'", "NotAI" = "'true'", "NotO" = "'false'", "RxMux" = "'false'"!][!//
                    [!IF "$CheckResult = 'true' and
                          ./PortPinPadTriggerMode = 'PORT_SCHMIDT_LEVEL_MODE' and
                          ./PortPinPadLevel != 'PORT_PDR_AL_AUTOMOTIVE_LEVEL'"!][!//
                        ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | [!//
                    [!ELSE!][!//
                        ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | [!//
                    [!ENDIF!][!//
                    [!CALL "Port_PinAttributesCheck", "NotRO" = "'true'", "NotDir" = "'PORT_PIN_IN'", "NotAI" = "'true'", "NotO" = "'false'", "RxMux" = "'false'"!][!//
                    [!IF "$CheckResult = 'true' and (./PortPinDriverStrength = 'PORT_DRIVER_STRENGTH_HIGH' and ./PortPinEnableSlewRate = 'true')"!][!//
                        (uint8)PORT_SLEWRATEMODE_ENABLE [!WS "1"!]|
                    [!ELSE!][!//
                        (uint8)PORT_SLEWRATEMODE_DISABLE |
                    [!ENDIF!][!//
                    [!CALL "Port_PinAttributesCheck", "NotRO" = "'false'", "NotDir" = "'PORT_PIN_OUT'", "NotAI" = "'true'", "NotO" = "'false'", "RxMux" = "'false'"!][!//
                    [!IF "$CheckResult = 'true'"!][!//
                        [!WS "1"!](uint8)[!"./PortPinPadTriggerMode"!] [!WS "6"!]|[!//
                    [!ELSE!][!//
                        [!WS "1"!](uint8)PORT_SCHMIDT_LEVEL_MODE [!WS "6"!]|[!//
                    [!ENDIF!][!//
                    [!CALL "Port_PinAttributesCheck", "NotRO" = "'true'", "NotDir" = "'PORT_PIN_IN'", "NotAI" = "'true'", "NotO" = "'false'", "RxMux" = "'false'"!][!//
                    [!IF "$CheckResult = 'true'"!][!//
                        [!WS "1"!](uint8)[!"./PortPinDriverStrength"!])[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "4"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ELSE!][!//
                        [!WS "1"!](uint8)PORT_DRIVER_STRENGTH_LOW)[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "4"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ENDIF!][!//
                    [!ENDSELECT!][!//
                [!ELSEIF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber]) and (./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'false'"!][!//
                    [!IF "contains(ecu:get('Port.DefaultHighStrengthCtrIPin'),concat('_',$PortPinIdNumber,'_'))"!][!//
                        ((uint8)PORT_PIN_NOTENABLE[!WS "12"!]| (uint8)PORT_DRIVER_STRENGTH_HIGH)[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "3"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ELSE!][!//
                        ((uint8)PORT_PIN_NOTENABLE)[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "49"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ENDIF!][!//
                [!ELSE!][!//
                    ((uint8)PORT_PIN_UNSUPPORT)[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "49"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }[!IF "num:i($PortCount) != num:i($AvailablePortTotalNumber)"!],[!ENDIF!]
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//
[!/**********************************************************************
MACRO:CG_GetPortPinDigitalFunctionsEnable_DFR
Get the Port Pin attributes : Enable/Disable digital functions
***********************************************************************/!]
[!MACRO "CG_GetPortPinDigitalFunctionsEnable_DFR", "Port" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!VAR "AvailablePortTotalNumber" = "ecu:get('Port.AvailablePortsTotalNumber')"!][!//
    [!VAR "PortCount" = "0"!][!//
    [!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
    {
        [!VAR "PortCount" = "num:i($PortCount + 1)"!][!//
        [!VAR "PortNumber" = "./PortNumber"!][!//
        [!INDENT "8"!][!//
        {
        [!INDENT "12"!][!//
        /*          Port[!"$PortNumber"!]: Pn_DFR          */
        [!FOR "PinNumber" = "0" TO "ecu:get('Port.MaxAvailablePinID')"!][!//
            [!VAR "PortPinIdNumber" = "num:i($PortNumber * 16 + $PinNumber)"!][!//
            [!/* Initialize the default analog input Port-Pins */!][!//
            [!IF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber]) and (./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'true'"!][!//
                [!SELECT "./PortPin/*[PortPinId = $PortPinIdNumber]"!][!//
                [!IF "./PortPinAnalogInputEnable = 'true' or (../../../../../PortGeneral/PortLvdsEnable = 'true' and (node:exists(../../PortLVDS/*[PortLVDSPairId = num:i($PortPinIdNumber)]) or node:exists(../../PortLVDS/*[PortLVDSPairId = num:i($PortPinIdNumber - 1)])))"!][!//
                    (uint8)PORT_FUNCTION_MODE_ANALOG[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!], [!ELSE!][!WS!][!ENDIF!][!WS "4"!]/* P[!"num:i($PortNumber)"!].[!"num:i($PinNumber)"!] */
                [!ELSE!][!//
                    (uint8)PORT_FUNCTION_MODE_DIGITAL[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "3"!]/* P[!"num:i($PortNumber)"!].[!"num:i($PinNumber)"!] */
                [!ENDIF!][!//
                [!ENDSELECT!][!//
            [!ELSE!][!//
                [!/* Initialize the default analog input Port-Pins */!][!//
                [!IF "contains(ecu:get('Port.DefaultAnalogInputCtrIPin'),concat('_',$PortPinIdNumber,'_'))"!][!//
                    (uint8)PORT_FUNCTION_MODE_ANALOG[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!], [!ELSE!][!WS!][!ENDIF!][!WS "4"!]/* P[!"num:i($PortNumber)"!].[!"num:i($PinNumber)"!] */
                [!/* Handling Port-Pins that are supported by the hardware but not enabled */!][!//
                [!ELSEIF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber]) and (./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'false'"!][!//
                    (uint8)PORT_PIN_NOTENABLE[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "11"!]/* P[!"num:i($PortNumber)"!].[!"num:i($PinNumber)"!] */
                [!/* Initialize the default analog input Port-Pins */!][!//
                [!ELSE!]
                    (uint8)PORT_PIN_UNSUPPORT[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "11"!]/* P[!"num:i($PortNumber)"!].[!"num:i($PinNumber)"!] */
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
        [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }[!IF "num:i($PortCount) != num:i($AvailablePortTotalNumber)"!],[!ENDIF!]
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//
[!/**********************************************************************
MACRO:CG_GetPortPinIoControlSelect_HWCR
Get the Port Pin attributes : IO controller selection
***********************************************************************/!]
[!MACRO "CG_GetPortPinIoControlSelect_HWCR"!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!VAR "AvailablePortTotalNumber" = "ecu:get('Port.AvailablePortsTotalNumber')"!][!//
    [!VAR "PortCount" = "0"!][!//
    [!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
    {
        [!VAR "PortCount" = "num:i($PortCount + 1)"!][!//
        [!VAR "PorNumber" = "./PortNumber"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
             /*          Port[!"./PortNumber"!]: Pn_HWCR         */
            [!FOR "PinNumber" = "0" TO "ecu:get('Port.MaxAvailablePinID')"!][!//
                [!VAR "PortPinIdNumber" = "./PortNumber"!][!//
                [!VAR "PortPinIdNumber" = "num:i($PortPinIdNumber * 16 + $PinNumber)"!][!//
                [!IF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber]) and (./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'true'"!][!//
                    [!SELECT "./PortPin/*[PortPinId = $PortPinIdNumber]"!][!//
                    [!IF "./PortPinDirection != 'PORT_PIN_IN' and
                          contains(ecu:get('Port.AvailabletPeripheralAltMode'), concat(./PortPinInitialMode, ' '))"!][!//
                        (uint8)PORT_CONTROLLER_VIA_PERIPHERAL[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "3"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ELSE!][!//
                        (uint8)PORT_CONTROLLER_VIA_PORT[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "9"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ENDIF!][!//
                    [!ENDSELECT!][!//
                [!ELSE!]
                    [!IF "contains(ecu:get('Port.DefaultPeripheralsCtrIPin'),concat('_',$PortPinIdNumber,'_'))"!][!//
                        (uint8)PORT_CONTROLLER_VIA_PERIPHERAL[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "3"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ELSEIF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber]) and (./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'false'"!][!//
                        (uint8)PORT_PIN_NOTENABLE[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ELSE!][!//
                        (uint8)PORT_PIN_UNSUPPORT[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }[!IF "num:i($PortCount) != num:i($AvailablePortTotalNumber)"!],[!ENDIF!]
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//
[!/**********************************************************************
MACRO:CG_GetPortPinPullUpModeSelect_PSR
Get the Port Pin attributes : Pull-Up mode Select
***********************************************************************/!]
[!MACRO "CG_GetPortPinPullUpModeSelect_PSR"!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!VAR "AvailablePortTotalNumber" = "ecu:get('Port.AvailablePortsTotalNumber')"!][!//
    [!VAR "PortCount" = "0"!][!//
    [!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
    {
        [!VAR "PortCount" = "num:i($PortCount + 1)"!][!//
        [!VAR "PorNumber" = "./PortNumber"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*          Port[!"./PortNumber"!]: Pn_PSR          */
            [!FOR "PinNumber" = "0" TO "ecu:get('Port.MaxAvailablePinID')"!][!//
                [!VAR "PortPinIdNumber" = "num:i($PorNumber * 16 + $PinNumber)"!][!//
                [!IF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber]) and (./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'true'"!][!//
                    [!SELECT "./PortPin/*[PortPinId = $PortPinIdNumber]"!][!//
                    [!CALL "Port_PinAttributesCheck", "NotRO" = "'false'", "NotDir" = "'PORT_PIN_OUT'", "NotAI" = "'true'", "NotO" = "'true'", "RxMux" = "'false'"!][!//
                    [!IF "$CheckResult = 'true' or (./PortPinDirection  = 'PORT_PIN_OUT' and ./PortPinOutputPushMode = 'PORT_OUTPUT_OPENDRAIN')"!][!//
                        (uint8)[!"./PortPinPullMode"!][!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "8"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ELSE!][!//
                        (uint8)PORT_INPUTMODE_PULLUP[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "10"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ENDIF!][!//
                    [!ENDSELECT!][!//
                [!ELSE!][!//
                    [!IF "not(node:exists(./PortPin/*[PortPinId = $PortPinIdNumber]))"!][!//
                        (uint8)PORT_PIN_UNSUPPORTPSR[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "8"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ELSEIF "contains(ecu:get('Port.DefaultNoPullDownCtrPin'),concat('_',num:i($PortPinIdNumber),'_'))"!][!//
                        (uint8)PORT_INPUTMODE_NONE[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "10"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ELSE!][!//
                        (uint8)PORT_INPUTMODE_PULLUP[!IF "num:i($PinNumber) != ecu:get('Port.MaxAvailablePinID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "8"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }[!IF "num:i($PortCount) != num:i($AvailablePortTotalNumber)"!],[!ENDIF!]
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetCanRxMuxSelect
Get the Port Pin attributes : CAN Input multiplexing function selection
***********************************************************************/!]
[!MACRO "CG_GetCanRxMuxSelect", "Index" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!VAR "CANRxMuxRegNum" = "num:i(0)"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($Index - 1)"!][!//
    [!VAR "CANRxMuxRegNum" = "num:i($CANRxMuxRegNum + text:split(ecu:get('Port.AvailableCANModule'), '_')[position() -1 = num:i($Count)])"!][!//
[!ENDFOR!][!//
[!VAR "LoopCount" = "text:split(ecu:get('Port.AvailableCANModule'), '_')[position() -1 = num:i($Index)]"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($LoopCount - 1)"!][!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*             CAN[!"$CANRxMuxRegNum"!]ISEL            */
            [!VAR "CANNodeCount" = "text:split(ecu:get('Port.AvailableCANModuleNodeNumber'), '_')[position() -1 = $CANRxMuxRegNum]"!][!//
            [!FOR "CANNode" = "0" TO "num:i($CANNodeCount - 1)"!][!//
                [!VAR "CAN_ID" = "concat('CAN', $CANRxMuxRegNum, $CANNode, '_RXD')"!][!/* CAN00_RXD */!][!//
                [!IF "contains($ALLPortPinInputConfig, $CAN_ID)"!][!/* ALLPortPinInputConfig : All input multiplexing configurations*/!][!//
                    [!VAR "RxMuxSubFunVlaue_CAN" = "substring-before(substring-after($ALLPortPinInputConfig, $CAN_ID),':')"!][!//
                    (uint8)PORT_CAN_RXD[!"$RxMuxSubFunVlaue_CAN"!][!IF "num:i($CANNode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "16"!]/* CAN[!"num:i($CANRxMuxRegNum)"!][!"num:i($CANNode)"!]RXSEL */
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE[!IF "num:i($CANNode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* CAN[!"num:i($CANRxMuxRegNum)"!][!"num:i($CANNode)"!]RXSEL */
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(7 - $CANNodeCount)"!][!//
                (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(7 - $CANNodeCount)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE    */
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    },
[!VAR "CANRxMuxRegNum" = "num:i($CANRxMuxRegNum + 1)"!][!//
[!ENDFOR!][!//
[!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetDSADCRxMuxSelect
Get the Port Pin attributes : DSADC Input multiplexing function selection
***********************************************************************/!]
[!MACRO "CG_GetDSADCRxMuxSelect", "Index" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!VAR "DSADCRxMuxRegNum" = "num:i(0)"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($Index - 1)"!][!//
    [!VAR "DSADCRxMuxRegNum" = "num:i($DSADCRxMuxRegNum + text:split(ecu:get('Port.AvailableDSADCModule'), '_')[position() -1 = num:i($Count)])"!][!//
[!ENDFOR!][!//
[!VAR "LoopCount" = "text:split(ecu:get('Port.AvailableDSADCModule'), '_')[position() -1 = num:i($Index)]"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($LoopCount - 1)"!][!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*            DSADCISEL[!"$DSADCRxMuxRegNum"!]           */
            [!VAR "DSADCNodeCount" = "text:split(ecu:get('Port.AvailableDSADCModuleNodeNumber'), '_')[position() -1 = $DSADCRxMuxRegNum]"!][!//
            [!FOR "DSADCNode" = "num:i(0)" TO "num:i($DSADCNodeCount - 1)"!][!//
                [!VAR "DSADCChannel" = "num:i($DSADCRxMuxRegNum * 8 + $DSADCNode)"!][!//
                [!VAR "DSADC_ID" = "concat('DSADC_ITR',$DSADCChannel)"!][!//
                [!IF "contains($ALLPortPinInputConfig, $DSADC_ID)"!][!//
                    [!VAR "RxMuxSubFunVlaue_DSADC" = "substring-before(substring-after($ALLPortPinInputConfig, $DSADC_ID),':')"!][!//
                    (uint8)PORT_DSADC_ITRx[!"$RxMuxSubFunVlaue_DSADC"!][!IF "num:i($DSADCNode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "13"!]/* TR[!"num:i($DSADCChannel)"!]SEL */
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE[!IF "num:i($DSADCNode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* TR[!"num:i($DSADCChannel)"!]SEL */
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(7 - $DSADCNodeCount)"!][!//
                (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(7 - $DSADCNodeCount)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE */
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    },
[!VAR "DSADCRxMuxRegNum" = "num:i($DSADCRxMuxRegNum + 1)"!][!//
[!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetETHRxMuxSelect
Get the Port Pin attributes : ETH input multiplexing function selection
***********************************************************************/!]
[!MACRO "CG_GetETHRxMuxSelect", "Index" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!VAR "ETHRxMuxRegNum" = "num:i(0)"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($Index - 1)"!][!//
    [!VAR "ETHRxMuxRegNum" = "num:i($ETHRxMuxRegNum + text:split(ecu:get('Port.AvailableETHModule'), '_')[position() -1 = num:i($Count)])"!][!//
[!ENDFOR!][!//
[!IF "contains(as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative, 'THA610X_LFBGA180')"!][!//
    [!VAR "IPName" = "'ETH_'"!][!//
[!ELSE!][!//
    [!VAR "IPName" = "'GETH_'"!][!//
[!ENDIF!][!//
[!VAR "LoopCount" = "text:split(ecu:get('Port.AvailableETHModule'), '_')[position() -1 = num:i($Index)]"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($LoopCount div 2 - 1)"!][!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*             ETHISEL[!"$ETHRxMuxRegNum"!]            */
            [!/* GETH_MDIOSEL */!][!//
                [!VAR "ETH_ID" = "concat($IPName, 'MDIO')"!][!//
                [!IF "contains($ALLPortPinInputConfig, $ETH_ID)"!][!//
                    [!VAR "RxMuxSubFunVlaue_ETH" = "substring-before(substring-after($ALLPortPinInputConfig, $ETH_ID),':')"!][!//
                    (uint8)PORT_MDIO[!"$RxMuxSubFunVlaue_ETH"!],[!WS "19"!]/* MDIOSEL  */
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE,[!WS "15"!]/* MDIOSEL  */
                [!ENDIF!][!//
            [!/* GETH_RXCKSEL */!][!//
                [!VAR "ETH_ID" = "concat($IPName, 'REFCLKA')"!][!//
                [!IF "contains($ALLPortPinInputConfig, $ETH_ID)"!][!//
                    (uint8)PORT_REFCLKA,[!WS "17"!]/* RXCKSEL  */
                [!ELSE!][!//
                    [!VAR "ETH_ID" = "concat($IPName, 'RXCLK')"!][!//
                    [!IF "contains($ALLPortPinInputConfig, $ETH_ID)"!][!//
                        [!VAR "RxMuxSubFunVlaue_ETH" = "substring-before(substring-after($ALLPortPinInputConfig, $ETH_ID),':')"!][!//
                        (uint8)PORT_RXCLK[!"$RxMuxSubFunVlaue_ETH"!],[!WS "18"!]/* RXCKSEL  */
                    [!ELSE!][!//
                        (uint8)PORT_RXRESERVE,[!WS "15"!]/* RXCKSEL  */
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!/* GETH_CRSSEL */!][!//
                [!VAR "ETH_ID" = "concat($IPName, 'CRS')"!][!//
                [!IF "contains($ALLPortPinInputConfig, $ETH_ID)"!][!//
                    [!VAR "RxMuxSubFunVlaue_ETH" = "substring-before(substring-after($ALLPortPinInputConfig,$ETH_ID),':')"!][!//
                    [!IF "contains($RxMuxSubFunVlaue_ETH, 'DV')"!][!//
                        [!IF "contains(substring-after(substring-after($ALLPortPinInputConfig,$ETH_ID),$ETH_ID),'$ETH_ID')"!][!//
                            [!VAR "RxMuxSubFunVlaue_TEMP" = "substring-before(substring-after(substring-after($ALLPortPinInputConfig,$ETH_ID),$ETH_ID),':')"!][!//
                            (uint8)PORT_CRS[!"$RxMuxSubFunVlaue_ETH"!],[!WS "24"!]/* CRSSEL   */
                        [!ELSE!][!//
                            (uint8)PORT_RXRESERVE,[!WS "15"!]/* CRSSEL   */
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        (uint8)PORT_CRS[!"$RxMuxSubFunVlaue_ETH"!],[!WS "20"!]/* CRSSEL   */
                    [!ENDIF!][!//
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE,[!WS "15"!]/* CRSSEL   */
                [!ENDIF!][!//
            [!/* GETH_COLSEL */!][!//
                [!VAR "ETH_ID" = "concat($IPName, 'COL')"!][!//
                [!IF "contains($ALLPortPinInputConfig,$ETH_ID)"!][!//
                    [!VAR "RxMuxSubFunVlaue_ETH" = "substring-before(substring-after($ALLPortPinInputConfig,$ETH_ID),':')"!][!//
                    (uint8)PORT_COL[!"$RxMuxSubFunVlaue_ETH"!],[!WS "20"!]/* COLSEL   */
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE,[!WS "15"!]/* COLSEL   */
                [!ENDIF!][!//
            [!/* GETH_DVSEL */!][!//
                [!VAR "ETH_ID" = "concat($IPName, 'RCTLA')"!][!//
                [!IF "contains($ALLPortPinInputConfig, $ETH_ID)"!][!//
                    (uint8)PORT_RCTLA,[!WS "17"!]/* DVSEL    */
                [!ELSE!][!//
                    [!VAR "ETH_ID1" = "concat($IPName, 'RXDV')"!][!//
                    [!VAR "ETH_ID2" = "concat($IPName, 'CRSDV')"!][!//
                    [!IF "contains($ALLPortPinInputConfig,$ETH_ID1)"!][!//
                        [!VAR "RxMuxSubFunVlaue_ETH" = "substring-before(substring-after($ALLPortPinInputConfig,$ETH_ID1),':')"!][!//
                        (uint8)PORT_RXDV[!"$RxMuxSubFunVlaue_ETH"!],[!WS "18"!]/* DVSEL    */
                    [!ELSE!][!//
                        [!IF "contains($ALLPortPinInputConfig,$ETH_ID2)"!][!//
                            [!VAR "RxMuxSubFunVlaue_ETH" = "substring-before(substring-after($ALLPortPinInputConfig,$ETH_ID2),':')"!][!//
                            (uint8)PORT_CRSDV[!"$RxMuxSubFunVlaue_ETH"!],[!WS "18"!]/* DVSEL    */
                        [!ELSE!][!//
                            (uint8)PORT_RXRESERVE,[!WS "15"!]/* DVSEL    */
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!/* GETH_RXERSEL */!][!//
                [!VAR "ETH_ID" = "concat($IPName, 'RXER')"!][!//
                [!IF "contains($ALLPortPinInputConfig,$ETH_ID)"!][!//
                    [!VAR "RxMuxSubFunVlaue_ETH" = "substring-before(substring-after($ALLPortPinInputConfig,$ETH_ID),':')"!][!//
                    (uint8)PORT_RXER[!"$RxMuxSubFunVlaue_ETH"!],[!WS "19"!]/* RXERSEL  */
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE,[!WS "15"!]/* RXERSEL  */
                [!ENDIF!][!//
            [!/* RESERVE */!][!//
                [!VAR "ETHNodeCount" = "text:split(ecu:get('Port.AvailableETHModuleNodeNumber'), '_')[position() -1 = 0]"!][!//
                [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(7 - $ETHNodeCount)"!][!//
                    (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(7 - $ETHNodeCount)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE  */
                [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    },
    [!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*             ETHISEL[!"num:i($ETHRxMuxRegNum + 1)"!]            */
            [!/* GETH_RXD<0-3>SEL */!][!//
                [!FOR "ETH_NUMBER" = "0" TO "3"!][!//
                    [!VAR "ETH_ID" = "concat($IPName, 'RXD',$ETH_NUMBER)"!][!//
                    [!IF "contains($ALLPortPinInputConfig,$ETH_ID)"!][!//
                        [!VAR "RxMuxSubFunVlaue_ETH" = "substring-before(substring-after($ALLPortPinInputConfig,$ETH_ID),':')"!][!//
                        (uint8)PORT_RXDx[!"$RxMuxSubFunVlaue_ETH"!],[!WS "19"!]/* RXD[!"$ETH_NUMBER"!]SEL  */
                    [!ELSE!][!//
                        (uint8)PORT_RXRESERVE,[!WS "15"!]/* RXD[!"$ETH_NUMBER"!]SEL  */
                    [!ENDIF!][!//
                [!ENDFOR!][!//
            [!/* GETH_TXCLKSEL */!][!//
                [!VAR "ETH_ID" = "concat($IPName, 'TXCLK')"!][!//
                [!IF "contains($ALLPortPinInputConfig, concat('; ', 'ETH_REFCLKA', ':'))"!][!//
                    (uint8)PORT_TXCLKB,[!WS "18"!]/* TXCLKSEL */
                [!ELSEIF "contains($ALLPortPinInputConfig,$ETH_ID)"!][!//
                    [!VAR "RxMuxSubFunVlaue_ETH" = "substring-before(substring-after($ALLPortPinInputConfig,$ETH_ID),':')"!][!//
                    (uint8)PORT_TXCLK[!"$RxMuxSubFunVlaue_ETH"!],[!WS "18"!]/* TXCLKSEL */
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE,[!WS "15"!]/* TXCLKSEL */
                [!ENDIF!][!//
            [!/* RESERVE */!][!//
                [!VAR "ETHNodeCount" = "text:split(ecu:get('Port.AvailableETHModuleNodeNumber'), '_')[position() -1 = 1]"!][!//
                [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(7 - $ETHNodeCount)"!][!//
                    (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(7 - $ETHNodeCount)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE  */
                [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    },
[!VAR "ETHRxMuxRegNum" = "num:i($ETHRxMuxRegNum + 1)"!][!//
[!ENDFOR!][!//
[!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetI2CRxMuxSelect
Get the Port Pin attributes : I2C input multiplexing function selection
***********************************************************************/!]
[!MACRO "CG_GetI2CRxMuxSelect", "Index" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!VAR "I2CRxMuxRegNum" = "num:i(0)"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($Index - 1)"!][!//
    [!VAR "I2CRxMuxRegNum" = "num:i($I2CRxMuxRegNum + text:split(ecu:get('Port.AvailableI2CModule'), '_')[position() -1 = num:i($Count)])"!][!//
[!ENDFOR!][!//
[!VAR "LoopCount" = "text:split(ecu:get('Port.AvailableI2CModule'), '_')[position() -1 = num:i($Index)]"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($LoopCount - 1)"!][!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*             I2C[!"$I2CRxMuxRegNum"!]ISEL            */
            [!VAR "I2C_SCL_ID" = "concat('I2C',$I2CRxMuxRegNum,'_SCL')"!][!//
            [!IF "contains($ALLPortPinInputConfig,$I2C_SCL_ID)"!][!//
                [!VAR "RxMuxSubFunVlaue_SCL" = "substring-before(substring-after($ALLPortPinInputConfig,$I2C_SCL_ID),':')"!][!//
                (uint8)PORT_SCL[!"$RxMuxSubFunVlaue_SCL"!],[!WS "20"!]/* SCLSEL   */
            [!ELSE!][!//
                (uint8)PORT_RXRESERVE,[!WS "15"!]/* SCLSEL   */
            [!ENDIF!][!//
            [!//
            [!VAR "I2C_SDA_ID" = "concat('I2C',$I2CRxMuxRegNum,'_SDA')"!][!//
            [!IF "contains($ALLPortPinInputConfig,$I2C_SDA_ID)"!][!//
                [!VAR "RxMuxSubFunVlaue_SDA" = "substring-before(substring-after($ALLPortPinInputConfig,$I2C_SDA_ID),':')"!][!//
                (uint8)PORT_SDA[!"$RxMuxSubFunVlaue_SDA"!],[!WS "20"!]/* SDASEL   */
            [!ELSE!][!//
                (uint8)PORT_RXRESERVE,[!WS "15"!]/* SDASEL   */
            [!ENDIF!][!//
            [!VAR "I2CNodeCount" = "text:split(ecu:get('Port.AvailableI2CModuleNodeNumber'), '_')[position() -1 = $I2CRxMuxRegNum]"!][!//
            [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(7 - $I2CNodeCount)"!][!//
                (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(7 - $I2CNodeCount)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE  */
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
    [!ENDINDENT!][!//
    },
[!VAR "I2CRxMuxRegNum" = "num:i($I2CRxMuxRegNum + 1)"!][!//
[!ENDFOR!][!//
[!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//
[!/**********************************************************************
MACRO:CG_GetASIRxMuxSelect
Get the Port Pin attributes : Lin input multiplexing function selection
***********************************************************************/!]
[!MACRO "CG_GetASIRxMuxSelect", "Index" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!VAR "ASIRxMuxRegNum" = "num:i(0)"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($Index - 1)"!][!//
    [!VAR "ASIRxMuxRegNum" = "num:i($ASIRxMuxRegNum + text:split(ecu:get('Port.AvailableASIModule'), '_')[position() -1 = num:i($Count)])"!][!//
[!ENDFOR!][!//
[!VAR "LoopCount" = "text:split(ecu:get('Port.AvailableASIModule'), '_')[position() -1 = num:i($Index)]"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($LoopCount - 1)"!][!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*             ASIISEL[!"$ASIRxMuxRegNum"!]            */
            [!VAR "ASINodeCount" = "text:split(ecu:get('Port.AvailableASIModuleNodeNumber'), '_')[position() -1 = num:i($ASIRxMuxRegNum)]"!][!//
            [!FOR "ASINode" = "0" TO "num:i($ASINodeCount - 1) "!][!//
                [!VAR "ASIChannel" = "num:i($ASIRxMuxRegNum * 8 + $ASINode)"!][!//
                [!VAR "ASI_ID" = "concat('ASI', $ASIChannel, '_ARX')"!][!//
                [!IF "contains($ALLPortPinInputConfig, $ASI_ID)"!][!//
                    [!VAR "RxMuxSubFunVlaue_ASI" = "substring-before(substring-after($ALLPortPinInputConfig,$ASI_ID),':')"!][!//
                    (uint8)PORT_ARX[!"$RxMuxSubFunVlaue_ASI"!][!IF "num:i($ASINode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "20"!]/* ARXSEL[!"$ASIChannel"!] */
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE[!IF "num:i($ASINode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* ARXSEL[!"$ASIChannel"!] */
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(7 - $ASINodeCount)"!][!//
                (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(7 - $ASINodeCount)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE */
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    },
[!VAR "ASIRxMuxRegNum" = "num:i($ASIRxMuxRegNum + 1)"!][!//
[!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetESPIRxMuxSelect
Get the Port Pin attributes : ESPIx input multiplexing function selection
***********************************************************************/!]
[!MACRO "CG_GetESPIRxMuxSelect", "Index" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!VAR "ESPIRxMuxRegNum" = "num:i(0)"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($Index - 1)"!][!//
    [!VAR "ESPIRxMuxRegNum" = "num:i($ESPIRxMuxRegNum + text:split(ecu:get('Port.AvailableESPIModule'), '_')[position() -1 = num:i($Count)])"!][!//
[!ENDFOR!][!//
[!VAR "LoopCount" = "text:split(ecu:get('Port.AvailableESPIModule'), '_')[position() -1 = num:i($Index)]"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($LoopCount - 1)"!][!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*            ESPI[!"$ESPIRxMuxRegNum"!]ISEL            */
            [!/* ESPIx_MRSTA */!][!//
            [!VAR "ESPINodeCount" = "text:split(ecu:get('Port.AvailableESPIModuleNodeNumber'), '_')[position() -1 = $ESPIRxMuxRegNum]"!][!//
            [!VAR "ESPI_ID" = "concat('ESPI',$ESPIRxMuxRegNum,'_MRST')"!][!/* ESPI0_MRST */!][!//
            [!VAR "RxMuxSubFunVlaue_ESPI" = "'FALSE'"!][!/* A */!][!//
            [!IF "contains($ALLPortPinInputConfig, $ESPI_ID)"!][!//
                [!VAR "RxMuxSubFunVlaue_ESPI" = "substring-before(substring-after($ALLPortPinInputConfig,$ESPI_ID),':')"!][!/* A */!][!//
                (uint8)PORT_MRST[!"$RxMuxSubFunVlaue_ESPI"!],[!WS "19"!]/* MRSTSEL  */
            [!ELSE!][!//
                (uint8)PORT_RXRESERVE,[!WS "15"!]/* MRSTSEL  */
            [!ENDIF!][!//
            [!/* ESPIx_MRSTA~H THA6412 ESPI5~8*/!][!//
            [!IF "$ESPINodeCount >= num:i(5)"!][!//
                [!IF "contains('ABCDEFGH', $RxMuxSubFunVlaue_ESPI)"!][!//
                    [!VAR "MRSTFlag" = "'A'"!][!/* I means that the ESPI extended RxMux function A~H is enabled */!][!//
                [!ELSEIF "contains('IJKLMNOP', $RxMuxSubFunVlaue_ESPI)"!][!//
                    [!VAR "MRSTFlag" = "'I'"!][!/* I means that the ESPI extended RxMux function I~P is enabled */!][!//
                [!ELSEIF "contains('QRSTV', $RxMuxSubFunVlaue_ESPI)"!][!//
                    [!VAR "MRSTFlag" = "'Q'"!][!/* I means that the ESPI extended RxMux function Q~V is enabled */!][!//
                [!ELSE!][!//
                    [!VAR "MRSTFlag" = "''"!][!/* I means that the ESPI extended RxMux function A~H is Disabled */!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!/* ESPIx_MTSRA, Used by Slave */!][!//
            [!VAR "ESPI_ID" = "concat('ESPI',$ESPIRxMuxRegNum,'_MTSR')"!][!//
            [!IF "contains($ALLPortPinInputConfig,$ESPI_ID)"!][!//
                [!VAR "RxMuxSubFunVlaue_ESPI" = "substring-before(substring-after($ALLPortPinInputConfig,$ESPI_ID),':')"!][!//
                (uint8)PORT_MTSR[!"$RxMuxSubFunVlaue_ESPI"!],[!WS "19"!]/* MTSRSEL */
            [!ELSE!][!//
                (uint8)PORT_RXRESERVE,[!WS "15"!]/* MTSRSEL  */
            [!ENDIF!][!//
            [!/* ESPIx_SCLKA */!][!//
            [!VAR "ESPI_ID" = "concat('ESPI',$ESPIRxMuxRegNum,'_SCLK')"!][!//
            [!IF "contains($ALLPortPinInputConfig,$ESPI_ID)"!][!//
                [!VAR "RxMuxSubFunVlaue_ESPI" = "substring-before(substring-after($ALLPortPinInputConfig,$ESPI_ID),':')"!][!//
                (uint8)PORT_SCLK[!"$RxMuxSubFunVlaue_ESPI"!],[!WS "19"!]/* SCLKSEL  */
            [!ELSE!][!//
                (uint8)PORT_RXRESERVE,[!WS "15"!]/* SCLKSEL  */
            [!ENDIF!][!//
            [!/* ESPIx_SLSIA */!][!//
            [!VAR "ESPI_ID" = "concat('ESPI',$ESPIRxMuxRegNum,'_SLSI')"!][!//
            [!IF "contains($ALLPortPinInputConfig,$ESPI_ID)"!][!//
                [!VAR "RxMuxSubFunVlaue_ESPI" = "substring-before(substring-after($ALLPortPinInputConfig,$ESPI_ID),':')"!][!//
                (uint8)PORT_SLSI[!"$RxMuxSubFunVlaue_ESPI"!],[!WS "19"!]/* SLSISEL  */
            [!ELSE!][!//
                (uint8)PORT_RXRESERVE,[!WS "15"!]/* SLSISEL  */
            [!ENDIF!][!//
            [!/* ESPIx_MRSTAH THA6412 ESPI5~8*/!][!//
            [!IF "$ESPINodeCount >= num:i(5)"!][!//
                [!IF "$MRSTFlag = 'A'"!][!//
                    (uint8)PORT_MRSTAH,[!WS "18"!]/* MRSTSELH */
                [!ELSEIF "$MRSTFlag = 'I'"!][!//
                    (uint8)PORT_MRSTIP,[!WS "18"!]/* MRSTSELH */
                [!ELSEIF "$MRSTFlag = 'Q'"!][!//
                    (uint8)PORT_MRSTQV,[!WS "18"!]/* MRSTSELH */
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE,[!WS "15"!]/* MRSTSELH  */
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(7 - $ESPINodeCount)"!][!//
                (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(7 - $ESPINodeCount)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE  */
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    },
[!VAR "ESPIRxMuxRegNum" = "num:i($ESPIRxMuxRegNum + 1)"!][!//
[!ENDFOR!][!//
[!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetSENTRxMuxSelect
Get the Port Pin attributes : SENTRx input multiplexing function selection
***********************************************************************/!]
[!MACRO "CG_GetSENTRxMuxSelect", "Index" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!VAR "SENTRxMuxRegNum" = "num:i(0)"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($Index - 1)"!][!//
    [!VAR "SENTRxMuxRegNum" = "num:i($SENTRxMuxRegNum + text:split(ecu:get('Port.AvailableSENTModule'), '_')[position() -1 = num:i($Count)])"!][!//
[!ENDFOR!][!//
[!VAR "LoopCount" = "text:split(ecu:get('Port.AvailableSENTModule'), '_')[position() -1 = num:i($Index)]"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($LoopCount - 1)"!][!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*            SENTISEL[!"num:i($SENTRxMuxRegNum * 8)"!]            */
            [!VAR "SENTNodeCount" = "text:split(ecu:get('Port.AvailableSENTModuleNodeNumber'), '_')[position() -1 = $SENTRxMuxRegNum]"!][!//
            [!FOR "SENTNode" = "num:i(0)" TO "num:i($SENTNodeCount - 1)"!][!//
                [!VAR "SENTChannel" = "num:i($SENTRxMuxRegNum * 8 + $SENTNode)"!][!//
                [!VAR "SENT_ID" = "concat('SENT_SENT', $SENTChannel)"!][!//
                [!VAR "RxMuxSubFunVlaue_SENT" = "text:grep(text:split($ALLPortPinInputConfig, '; '), concat($SENT_ID, '[a-zA-Z]*:.*'))"!][!//
                [!IF "$RxMuxSubFunVlaue_SENT != '[]'"!][!//
                    [!VAR "RxMuxSubFunVlaue_SENT" = "substring-before(substring-after($RxMuxSubFunVlaue_SENT, $SENT_ID),':')"!][!//
                    (uint8)PORT_SENTx[!"$RxMuxSubFunVlaue_SENT"!][!IF "num:i($SENTNode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "18"!]/* SENT[!"$SENTChannel"!]SEL */
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE[!IF "num:i($SENTNode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* SENT[!"$SENTChannel"!]SEL */
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(7 - $SENTNodeCount)"!][!//
                (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(7 - $SENTNodeCount)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE    */
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    },
[!VAR "SENTRxMuxRegNum" = "num:i($SENTRxMuxRegNum + 1)"!][!//
[!ENDFOR!][!//
[!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetIOMMONRxMuxSelect
Get the Iom monitoring signal group
***********************************************************************/!]
[!MACRO "CG_GetIOMMONRxMuxSelect", "Index" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!VAR "IOMMONRxMuxRegNum" = "num:i(0)"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($Index - 1)"!][!//
    [!VAR "IOMMONRxMuxRegNum" = "num:i($IOMMONRxMuxRegNum + text:split(ecu:get('Port.AvailableIOMMONModule'), '_')[position() -1 = num:i($Count)])"!][!//
[!ENDFOR!][!//
[!VAR "LoopCount" = "text:split(ecu:get('Port.AvailableIOMMONModule'), '_')[position() -1 = num:i($Index)]"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($LoopCount - 1)"!][!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            [!/* Get the IOMMON ID based on whether the IOMMON hardware number is continuous */!][!//
            [!IF "ecu:get('Port.AvailableIOMMONModuleIDNumber') = ''"!][!//
                [!VAR "IOMModuleID" = "num:i($IOMMONRxMuxRegNum div 2)"!][!//
            [!ELSE!][!//
                [!VAR "IOMModuleID" = "text:split(ecu:get('Port.AvailableIOMMONModuleIDNumber'), '_')[position() -1 = num:i($IOMMONRxMuxRegNum div 2)]"!][!//
            [!ENDIF!][!//
            /*           IOMMON[!"$IOMModuleID"!]SEL[!"num:i($IOMMONRxMuxRegNum mod 2 * 8)"!]           */
            [!VAR "IOMNodeCount" = "text:split(ecu:get('Port.AvailableIOMMONModuleNodeNumber'), '_')[position() -1 = $IOMMONRxMuxRegNum]"!][!//
            [!FOR "IOMNode" = "num:i(0)" TO "num:i($IOMNodeCount - 1)"!][!//
                [!VAR "IOMChannel" = "num:i($IOMMONRxMuxRegNum mod 2 * 8 + $IOMNode)"!][!//
                [!VAR "IOM_ID" = "concat('IOM',$IOMModuleID,'_SCL')"!][!//
                [!IF "ecu:has(concat('Port.MUL_IOMMON',$IOMModuleID,'_',$IOMChannel))"!][!//
                    [!VAR "IOMOutputMessage" = "ecu:get(concat('Port.MUL_IOMMON',$IOMModuleID,'_',$IOMChannel))"!][!//
                    [!IF "contains($ALLPortPinOutputConfig, concat($IOMOutputMessage, ':'))"!][!//
                        [!VAR "RxMux_PortPin_Vlaue" = "substring-before(substring-after($ALLPortPinOutputConfig,concat($IOMOutputMessage,':P')),';')"!][!//
                        [!VAR "Port_Vlaue" = "substring-before($RxMux_PortPin_Vlaue,'.')"!][!//
                        [!VAR "Pin_Vlaue" = "substring-after($RxMux_PortPin_Vlaue,'.')"!][!//
                            (uint8)PORT_RXMUX_IOMMON[!"$IOMModuleID"!]_[!"$Port_Vlaue"!]_[!"$Pin_Vlaue"!][!IF "num:i($IOMChannel mod 8) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "6"!]/* MON[!"$IOMModuleID"!]SEL[!"$IOMChannel"!] */
                    [!ELSE!][!//
                        (uint8)PORT_RXRESERVE[!IF "num:i($IOMNode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* MON[!"$IOMModuleID"!]SEL[!"$IOMChannel"!] */
                    [!ENDIF!][!//
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE[!IF "num:i($IOMNode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* MON[!"$IOMModuleID"!]SEL[!"$IOMChannel"!] */
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(7 - $IOMNodeCount)"!][!//
                (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(7 - $IOMNodeCount)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE */
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    },
[!VAR "IOMMONRxMuxRegNum" = "num:i($IOMMONRxMuxRegNum + 1)"!][!//
[!ENDFOR!][!//
[!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetDBGTraceRxMuxSelect
Get the Port Pin attributes : Debug trig Input multiplexing function selection
***********************************************************************/!]
[!MACRO "CG_GetDBGTraceRxMuxSelect", "Index" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!VAR "DBGRxMuxRegNum" = "num:i(0)"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($Index - 1)"!][!//
    [!VAR "DBGRxMuxRegNum" = "num:i($DBGRxMuxRegNum + text:split(ecu:get('Port.AvailableDBGModule'), '_')[position() -1 = num:i($Count)])"!][!//
[!ENDFOR!][!//
[!VAR "LoopCount" = "text:split(ecu:get('Port.AvailableDBGModule'), '_')[position() -1 = num:i($Index)]"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($LoopCount - 1)"!][!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*            DBGTRIGSEL           */
            [!VAR "DBGNodeCount" = "text:split(ecu:get('Port.AvailableDBGModuleNodeNumber'), '_')[position() -1 = $DBGRxMuxRegNum]"!][!//
            [!FOR "DBGNode" = "0" TO "num:i($DBGNodeCount - 1)"!][!//
                [!IF "contains($ALLPortPinInputConfig, 'TRIG_IO')"!][!//
                    (uint8)PORT_TRIG_IO[!IF "num:i($DBGNode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "17"!]/* TRIGSEL */
                [!ELSEIF "contains($ALLPortPinInputConfig, 'TRIG_IN')"!][!//
                    (uint8)PORT_TRIG_IN[!IF "num:i($DBGNode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "17"!]/* TRIGSEL */
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE[!IF "num:i($DBGNode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* TRIGSEL */
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(7 - $DBGNodeCount)"!][!//
                (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(7 - $DBGNodeCount)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE */
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }[!IF "not(contains(as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative, 'THA6206'))"!],[!ENDIF!]
[!VAR "DBGRxMuxRegNum" = "num:i($DBGRxMuxRegNum + 1)"!][!//
[!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetPSI5RxMuxSelect
Get the Port Pin attributes : Psi5 Input multiplexing function selection
***********************************************************************/!]
[!MACRO "CG_GetPSI5RxMuxSelect", "Index" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!VAR "PSI5RxMuxRegNum" = "num:i(0)"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($Index - 1)"!][!//
    [!VAR "PSI5RxMuxRegNum" = "num:i($PSI5RxMuxRegNum + text:split(ecu:get('Port.AvailablePSI5Module'), '_')[position() -1 = num:i($Count)])"!][!//
[!ENDFOR!][!//
[!VAR "LoopCount" = "text:split(ecu:get('Port.AvailablePSI5Module'), '_')[position() -1 = num:i($Index)]"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($LoopCount - 1)"!][!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*             PSI5RXSEL                */
            [!VAR "PSI5NodeCount" = "text:split(ecu:get('Port.AvailablePSI5ModuleNodeNumber'), '_')[position() -1 = num:i($PSI5RxMuxRegNum)]"!][!//
            [!FOR "PSI5Node" = "0" TO "num:i($PSI5NodeCount - 1) "!][!//
                [!VAR "PSI5Channel" = "num:i($PSI5RxMuxRegNum * 8 + $PSI5Node)"!][!//
                [!VAR "PSI5_ID" = "concat('PSI5_RX', $PSI5Channel)"!][!//
                [!IF "contains($ALLPortPinInputConfig, $PSI5_ID)"!][!//
                    [!VAR "RxMuxSubFunVlaue_PSI5" = "substring-before(substring-after($ALLPortPinInputConfig,$PSI5_ID),':')"!][!//
                    (uint8)PORT_RXx[!"$RxMuxSubFunVlaue_PSI5"!][!IF "num:i($PSI5Node) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "18"!]/* RX[!"$PSI5Channel"!]SEL  */
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE[!IF "num:i($PSI5Node) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RX[!"$PSI5Channel"!]SEL  */
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(7 - $PSI5NodeCount)"!][!//
                (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(7 - $PSI5NodeCount)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE */
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }
[!VAR "PSI5RxMuxRegNum" = "num:i($PSI5RxMuxRegNum + 1)"!][!//
[!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetIOMPINRxMuxSelect
Get the Port Pin attributes : IOMPIN input multiplexing function selection
***********************************************************************/!]
[!MACRO "CG_GetIOMPINRxMuxSelect", "Index" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!VAR "IOMPINRxMuxRegNum" = "num:i(0)"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($Index - 1)"!][!//
    [!VAR "IOMPINRxMuxRegNum" = "num:i($IOMPINRxMuxRegNum + text:split(ecu:get('Port.AvailableIOMPINModule'), '_')[position() -1 = num:i($Count)])"!][!//
[!ENDFOR!][!//
[!VAR "LoopCount" = "text:split(ecu:get('Port.AvailableIOMPINModule'), '_')[position() -1 = num:i($Index)]"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($LoopCount - 1)"!][!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*            IOMPINSEL            */
            [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(2)"!][!//
                (uint8)PORT_RXRESERVE,[!WS "15"!]/* RESERVE  */
            [!ENDFOR!][!//
            [!VAR "IOMPINNodeCount" = "text:split(ecu:get('Port.AvailableIOMPINModuleNodeNumber'), '_')[1]"!][!//
            [!FOR "IOMPINNode" = "num:i(0)" TO "num:i($IOMPINNodeCount - 1)"!][!//
                [!VAR "IOMPINChannel" = "num:i(13 + $IOMPINNode)"!][!//
                [!VAR "IOMPIN_ID" = "concat('IOM_PIN_', $IOMPINChannel)"!][!//
                [!IF "contains($ALLPortPinInputConfig, $IOMPIN_ID)"!][!//
                    [!VAR "RxMuxSubFunVlaue_IOMPIN" = "substring-before(substring-after($ALLPortPinInputConfig, concat($IOMPIN_ID,':P')),';')"!][!//
                    [!VAR "Port_Vlaue" = "substring-before($RxMuxSubFunVlaue_IOMPIN,'.')"!][!//
                    [!VAR "Pin_Vlaue" = "substring-after($RxMuxSubFunVlaue_IOMPIN,'.')"!][!//
                    (uint8)(PORT_RXMUX_IOMPIN[!"$IOMPINChannel"!]_[!"$Port_Vlaue"!]_[!"$Pin_Vlaue"!] << [!"num:i($IOMPINNode + 1)"!]U)[!IF "num:i($IOMPINNode) != num:i(2)"!] |[!ELSE!],[!WS!][!ENDIF!][!WS "4"!]/* PIN[!"$IOMPINChannel"!]SEL, Bit[!"$IOMPINChannel"!] */
                [!ELSE!][!//
                    (uint8)(PORT_RXRESERVE << [!"num:i($IOMPINNode + 1)"!]U)[!IF "num:i($IOMPINNode) != num:i(2)"!] |[!ELSE!],[!WS!][!ENDIF!][!WS "6"!]/* PIN[!"$IOMPINChannel"!]SEL, Bit[!"$IOMPINChannel"!] */
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(3)"!][!//
                (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(3)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE  */
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    },
[!VAR "IOMPINRxMuxRegNum" = "num:i($IOMPINRxMuxRegNum + 1)"!][!//
[!ENDFOR!][!//
[!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetGTMRxMuxSelect
Get the Port Pin attributes : GTM input multiplexing function selection
***********************************************************************/!]
[!MACRO "CG_GetGTMRxMuxSelect", "Index" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!VAR "GTMRxMuxRegNum" = "num:i(0)"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($Index - 1)"!][!//
    [!VAR "GTMRxMuxRegNum" = "num:i($GTMRxMuxRegNum + text:split(ecu:get('Port.AvailableGTMModule'), '_')[position() -1 = num:i($Count)])"!][!//
[!ENDFOR!][!//
[!VAR "LoopCount" = "text:split(ecu:get('Port.AvailableGTMModule'), '_')[position() -1 = num:i($Index)]"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($LoopCount - 1)"!][!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*            GTMSEL            */
            [!VAR "GTMNodeCount" = "text:split(ecu:get('Port.AvailableGTMModuleNodeNumber'), '_')[position() -1 = $GTMRxMuxRegNum]"!][!//
            [!FOR "GTMNode" = "num:i(0)" TO "num:i($GTMNodeCount - 1)"!][!//
                [!VAR "GTMChannel" = "num:i($GTMRxMuxRegNum * 8 + $GTMNode)"!][!//
                [!VAR "GTM_ID" = "concat('TIO', $GTMChannel, '_INPUT_CHANNEL')"!][!//
                [!IF "contains($ALLPortPinInputConfig, $GTM_ID)"!][!//
                    [!VAR "RxMuxSubFunVlaue_GTM" = "substring-before(substring-after($ALLPortPinInputConfig,concat($GTM_ID,':P')),';')"!][!//
                    [!VAR "Port_Vlaue" = "substring-before($RxMuxSubFunVlaue_GTM,'.')"!][!//
                    [!VAR "Pin_Vlaue" = "substring-after($RxMuxSubFunVlaue_GTM,'.')"!][!//
                    (uint8)PORT_RXMUX_GTMTIO[!"$GTMChannel"!]_[!"$Port_Vlaue"!]_[!"$Pin_Vlaue"!][!IF "num:i($GTMNode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "7"!]/* TIO[!"$GTMChannel"!]SEL */
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE[!IF "num:i($GTMNode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* TIO[!"$GTMChannel"!]SEL */
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(7 - $GTMNodeCount)"!][!//
                (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(7 - $GTMNodeCount)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE */
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    },
[!VAR "GTMRxMuxRegNum" = "num:i($GTMRxMuxRegNum + 1)"!][!//
[!ENDFOR!][!//
[!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//


[!/**********************************************************************
MACRO:CG_GetEXTIRxMuxSelect
Get the Port Pin attributes : EXTI input multiplexing function selection
***********************************************************************/!]
[!MACRO "CG_GetEXTIRxMuxSelect", "Index" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!VAR "EXTIRxMuxRegNum" = "num:i(0)"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($Index - 1)"!][!//
    [!VAR "EXTIRxMuxRegNum" = "num:i($EXTIRxMuxRegNum + text:split(ecu:get('Port.AvailableEXTIModule'), '_')[position() -1 = num:i($Count)])"!][!//
[!ENDFOR!][!//
[!VAR "LoopCount" = "text:split(ecu:get('Port.AvailableEXTIModule'), '_')[position() -1 = num:i($Index)]"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($LoopCount - 1)"!][!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*            EXTISEL            */
            [!VAR "EXTINodeCount" = "text:split(ecu:get('Port.AvailableEXTIModuleNodeNumber'), '_')[1]"!][!//
            [!FOR "EXTINode" = "num:i(0)" TO "num:i($EXTINodeCount - 1)"!][!//
                [!IF "contains($ALLPortPinInputConfig, 'E_REQ7_2')"!][!//
                    [!VAR "RxMuxSubFunVlaue_EXTI" = "substring-before(substring-after($ALLPortPinInputConfig, 'E_REQ7_2:P'),';')"!][!//
                    [!VAR "Port_Vlaue" = "substring-before($RxMuxSubFunVlaue_EXTI,'.')"!][!//
                    [!VAR "Pin_Vlaue" = "substring-after($RxMuxSubFunVlaue_EXTI,'.')"!][!//
                    (uint8)PORT_RXMUX_EXTIREQ72_[!"$Port_Vlaue"!]_[!"$Pin_Vlaue"!][!IF "num:i($EXTINode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "4"!]/* EXTIREQ72SEL */
                [!ELSE!][!//
                    (uint8)PORT_RXRESERVE[!IF "num:i($EXTINode) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* EXTIREQ72SEL */
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(7 - $EXTINodeCount)"!][!//
                (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(7 - $EXTINodeCount)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE */
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    },
[!VAR "EXTIRxMuxRegNum" = "num:i($EXTIRxMuxRegNum + 1)"!][!//
[!ENDFOR!][!//
[!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetRxMuxSelectReserve
Reserve the unused addresses of the input multiplexing registers
***********************************************************************/!]
[!MACRO "CG_GetRxMuxSelectReserve", "RegNum" = ""!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!FOR "Count" = "num:i(0)" TO "num:i($RegNum - 1)"!][!//
    {/* RxMux: [!"$RxMuxCount"!] */
        [!VAR "RxMuxCount" = "num:i($RxMuxCount + 1)"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*            RXMUX RESERVE            */
            [!FOR "RXMUXRSVCount" = "num:i(0)" TO "num:i(7)"!][!//
                (uint8)PORT_RXRESERVE[!IF "num:i($RXMUXRSVCount) != num:i(7)"!],[!ELSE!][!WS!][!ENDIF!][!WS "15"!]/* RESERVE  */
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    },
[!ENDFOR!][!//
[!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetPinModeChangeEnable
Get the Port Pin attributes : Enable the pin mode can be changed
***********************************************************************/!]
[!MACRO "CG_GetPinModeChangeEnable"!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!VAR "AvailablePortTotalNumber" = "ecu:get('Port.AvailablePortsTotalNumber')"!][!//
    [!VAR "PortCount" = "0"!][!//
    [!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
    {
        [!VAR "PortCount" = "num:i($PortCount + 1)"!][!//
        [!VAR "PorNumber" = "./PortNumber"!][!//
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /*      Port[!"./PortNumber"!]: Pin Mode Change     */
            [!FOR "PinNumber" = "0" TO "ecu:get('Port.MaxAvailablePinID')"!][!//
                [!VAR "PortPinIdNumber" = "num:i($PorNumber * 16 + $PinNumber)"!][!//
                [!IF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber])"!][!//
                    [!IF "(./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'true'"!][!//
                        [!SELECT "./PortPin/*[PortPinId = $PortPinIdNumber]"!][!//
                            [!IF "./PortPinModeChangeable = 'true'"!][!//
                                (uint8)PORT_PIN_ALT_CHANGEABLE,[!WS "6"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                            [!ELSE!][!//
                                (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,[!WS "2"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                            [!ENDIF!][!//
                        [!ENDSELECT!][!//
                    [!ELSE!][!//
                        (uint8)PORT_PIN_NOTENABLE,[!WS "11"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                    [!ENDIF!][!//
                [!ELSE!][!//
                    (uint8)PORT_PIN_UNSUPPORT,[!WS "11"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                [!ENDIF!][!//
            [!ENDFOR!][!//
            (uint16)PORT_RXRESERVE[!WS "15"!]/* RXRESERVE */
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }[!IF "num:i($PortCount) != num:i($AvailablePortTotalNumber)"!],[!ENDIF!]
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetPinDirectionChangeEnable
Get the Port Pin attributes : Enable pin direction can be changed
***********************************************************************/!]
[!MACRO "CG_GetPinDirectionChangeEnable"!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!VAR "AvailablePortTotalNumber" = "ecu:get('Port.AvailablePortsTotalNumber')"!][!//
    [!VAR "PortCount" = "0"!][!//
    [!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
    {
        [!VAR "PortCount" = "num:i($PortCount + 1)"!][!//
        [!VAR "PorNumber" = "./PortNumber"!][!//
        [!INDENT "8"!][!//
        {
        [!INDENT "12"!][!//
        /*   Port[!"./PortNumber"!]: Pin Direction Change   */
        [!FOR "PinNumber" = "0" TO "ecu:get('Port.MaxAvailablePinID')"!][!//
            [!VAR "PortPinIdNumber" = "num:i($PorNumber * 16 + $PinNumber)"!][!//
            [!IF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber])"!][!//
                [!IF "(./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'true'"!][!//
                    [!SELECT "./PortPin/*[PortPinId = $PortPinIdNumber]"!][!//
                        [!IF "./PortPinDirectionChangeable = 'true'"!][!//
                            (uint8)PORT_PIN_DIR_CHANGEABLE,[!WS "6"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                        [!ELSE!][!//
                            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,[!WS "2"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                        [!ENDIF!][!//
                    [!ENDSELECT!][!//
                [!ELSE!][!//
                    (uint8)PORT_PIN_NOTENABLE,[!WS "11"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
                [!ENDIF!][!//
            [!ELSE!][!//
                (uint8)PORT_PIN_UNSUPPORT,[!WS "11"!]/* P[!"$PorNumber"!].[!"num:i($PinNumber)"!] */
            [!ENDIF!][!//
        [!ENDFOR!][!//
        (uint16)PORT_RXRESERVE[!WS "15"!]/* RXRESERVE */
        [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }[!IF "num:i($PortCount) != num:i($AvailablePortTotalNumber)"!],[!ENDIF!]
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/**********************************************************************
MACRO:CG_GetPinHwSupportAltModes
Get the Port Pin attributes :ALT mode
***********************************************************************/!]
[!MACRO "CG_GetPinHwSupportAltModes"!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!VAR "AvailablePortTotalNumber" = "ecu:get('Port.AvailablePortsTotalNumber')"!][!//
    [!VAR "PortCount" = "0"!][!//
    [!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
    {
        [!VAR "PortCount" = "num:i($PortCount + 1)"!][!//
        [!VAR "PorNumber" = "./PortNumber"!][!//
        [!INDENT "8"!][!//
        {
        [!INDENT "12"!][!//
        [!IF "contains(ecu:get('Port.AvailableReadOnlyPorts'),concat('_',./PortNumber,'_'))"!][!//
            /*         Port[!"./PortNumber"!] ReadOnly        */
            [!FOR "PinNumber" = "0" TO "num:i(ecu:get('Port.MaxAvailablePinID'))"!][!//
                0x0000U[!IF "($PinNumber != num:i(ecu:get('Port.MaxAvailablePinID')))"!],[!ELSE!][!WS!][!ENDIF!][!WS "8"!]/* Pin[!"$PinNumber"!] */
            [!ENDFOR!][!//
        [!ELSE!][!//
            /*              Port[!"./PortNumber"!]            */
            [!FOR "PinNumber" = "0" TO "ecu:get('Port.MaxAvailablePinID')"!][!//
                [!VAR "PortPinIdNumber" = "num:i($PorNumber * 16 + $PinNumber)"!][!//
                [!VAR "Pin_Mode" = "num:i(0)"!][!//
                [!IF "node:exists(./PortPin/*[PortPinId = $PortPinIdNumber])"!][!//
                    [!IF "(./PortPin/*[PortPinId = $PortPinIdNumber]/PortPinEnable) = 'true'"!][!//
                        [!FOR "ModeNumber" = "0" TO "num:i(ecu:get('Port.MaxPortPinModeNumber'))"!][!//
                            [!IF "contains(ecu:get(concat('Port.OutputModes',substring-after(num:inttohex(num:i(./PortNumber * 16 + $PinNumber)),'x'))),concat('_O',($ModeNumber),'_'))"!][!//
                                [!VAR "Pin_Mode" = "bit:bitset(num:i($Pin_Mode),$ModeNumber)"!][!//
                            [!ENDIF!][!//
                        [!ENDFOR!][!//
                        [!"num:inttohex($Pin_Mode,4)"!]U[!IF "($PinNumber != num:i(ecu:get('Port.MaxAvailablePinID')))"!],[!ELSE!][!WS!][!ENDIF!][!WS "8"!]/* Alt mask: supported by Pin[!"$PinNumber"!] */
                    [!ELSE!][!//
                        0x0000U[!IF "($PinNumber != num:i(ecu:get('Port.MaxAvailablePinID')))"!],[!ELSE!][!WS!][!ENDIF!][!WS "8"!]/* Alt mask: not enabled by Pin[!"$PinNumber"!] */
                    [!ENDIF!][!//
                [!ELSE!][!//
                    0x0000U[!IF "($PinNumber != num:i(ecu:get('Port.MaxAvailablePinID')))"!],[!ELSE!][!WS!][!ENDIF!][!WS "8"!]/* Alt mask: not supported by Pin[!"$PinNumber"!] */
                [!ENDIF!][!//
            [!ENDFOR!][!//
        [!ENDIF!][!//
        [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }[!IF "num:i($PortCount) != num:i($AvailablePortTotalNumber)"!],[!ENDIF!]
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: Port_GetLVDSConfigNumber
  Get PortPin Pair Config message
*****************************************************************************/!]
[!MACRO "Port_GetLVDSConfigNumber"!][!//
[!//
[!NOCODE!][!//
[!AUTOSPACING!][!//
[!VAR "LVDSPairTotalNumber" = "num:i(0)"!][!//
[!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
    [!VAR "PortNum" = "./PortNumber"!][!//
    [!IF "contains(ecu:get('Port.AvailableLVDSPorts'),concat('_',$PortNum,'_'))"!][!//
        [!FOR "PortIndex" = "num:i(1)" TO "num:i(ecu:get(concat('Port.Port',$PortNum,'AvailableLVDSPairNum')))"!][!//
            [!IF "node:exists(./PortLVDS/*[position() = num:i($PortIndex)])"!][!//
                [!VAR "LVDSPairTotalNumber" = "num:i($LVDSPairTotalNumber + 1)"!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
  MACRO: Port_GetLVDSConfig
  Get PortPin Pair Config message
*****************************************************************************/!]
[!MACRO "Port_GetLVDSConfig"!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
[!VAR "LVDS_Pair_Number" = "num:i(0)"!][!//
[!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
    [!VAR "PortNum" = "./PortNumber"!][!//
    [!IF "contains(ecu:get('Port.AvailableLVDSPorts'),concat('_',$PortNum,'_'))"!][!//
        [!FOR "PortIndex" = "num:i(1)" TO "num:i(ecu:get(concat('Port.Port',$PortNum,'AvailableLVDSPairNum')))"!][!//
            [!IF "node:exists(./PortLVDS/*[position() = num:i($PortIndex)])"!][!//
                [!SELECT "./PortLVDS/*[position() = num:i($PortIndex)]"!][!//
                    [!VAR "PortLVDSPinPair" = "./PortLVDSPinPair"!][!//
                    [!VAR "Pin0" = "substring-before(substring-after($PortLVDSPinPair,'PAIR_PIN_'),'_')"!][!//
                    [!VAR "Pin1" = "substring-after(substring-after($PortLVDSPinPair,'PAIR_PIN_'),'_')"!][!//
                    [!VAR "LVDSRNumber" = "ecu:get(concat('Port.Port',$PortNum,$PortLVDSPinPair))"!][!//
                    [!VAR "LVDS_Pair_Number" = "num:i($LVDS_Pair_Number + 1)"!][!//
                        {
                            [!INDENT "8"!][!//
                            [!"$PortNum"!],[!WS "8"!]/* LVDS PortNumber */
                            [!"$Pin0"!],[!WS "9"!]/* LVDS PinNumber0 */
                            [!"$Pin1"!],[!WS "9"!]/* LVDS PinNumber1 */
                            [!"$LVDSRNumber"!],[!WS "9"!]/* LVDS LVDSR_Pair Number */
                            /* LVDSR register configuration value */
                            [!IF "./PortLVDSTerminationResistorEnable = 'LVDS_RTERM_ENABLE'"!][!//
                                ((uint8)PORT_[!"./PortLVDSMode"!] | (uint8)PORT_[!"./PortLVDSTerminationResistorEnable"!] | (uint8)PORT_[!"./PortLVDSTerminationResistorVal"!] |
                                [!WS "1"!](uint8)PORT_[!"./PortLVDSCurrentAndSwing"!] | (uint8)PORT_[!"./PortLVDSOutputCurrentRatioTrim"!] |
                                [!WS "1"!](uint8)PORT_[!"./PortLVDSBiasVolSelect"!])
                            [!ELSE!][!//
                                ((uint8)PORT_[!"./PortLVDSMode"!] | (uint8)PORT_[!"./PortLVDSTerminationResistorEnable"!] | (uint8)PORT_[!"./PortLVDSCurrentAndSwing"!] |
                                [!WS "1"!](uint8)PORT_[!"./PortLVDSOutputCurrentRatioTrim"!] | (uint8)PORT_[!"./PortLVDSBiasVolSelect"!])
                            [!ENDIF!][!//
                            [!ENDINDENT!][!//
                        }[!IF "num:i($LVDS_Pair_Number) != num:i($LVDSPairTotalNumber)"!],[!ELSE!][!WS!][!ENDIF!]
                [!ENDSELECT!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
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
    [!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
        [!VAR "Port_Temp" = "num:i(0)"!][!//
        [!VAR "PortNumber" = "./PortNumber"!][!//
        [!FOR "PinNumber" = "0" TO "num:i(ecu:get('Port.MaxAvailablePinID'))"!][!//
            [!IF "contains(ecu:get(concat('Port.Port',$PortNumber,'_AvailablePins')),concat('_',$PinNumber,'_'))"!][!//
                [!VAR "Port_Temp" = "bit:bitset(num:i($Port_Temp),$PinNumber)"!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
            [!"num:inttohex($Port_Temp,4)"!]U[!IF "$PortNumber != ecu:get('Port.MaxAvailablePortID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "8"!]/* Port[!"$PortNumber"!] */
    [!ENDLOOP!][!//
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
            0x[!"substring-after(text:toupper(num:inttohex($PortCount, 2)), 'X')"!]U[!IF "$PortNumber != ecu:get('Port.MaxAvailablePortID')"!],[!ELSE!][!WS!][!ENDIF!][!//
            [!IF "contains(ecu:get('Port.AvailableReadOnlyPorts'),concat('_',$PortNumber,'_'))"!][!//
                [!WS "10"!]/* Port[!"$PortNumber"!] ReadOnly*/
            [!ELSE!][!//
                [!WS "10"!]/* Port[!"$PortNumber"!] */
            [!ENDIF!][!//
            [!VAR "PortCount" = "num:i($PortCount + 1)"!][!//
        [!ELSE!][!//
            0xFFU[!IF "$PortNumber != ecu:get('Port.MaxAvailablePortID')"!],[!ENDIF!][!WS "10"!]/* Port[!"$PortNumber"!] UnSupport*/
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//


[!/*************************************************************
    Macro: CG_GenePortHwUnitMap
    Macro to generate definition to indicate the port pins that are
    available in the microcontroller
***************************************************************/!]
[!MACRO "CG_GenePortHwUnitMap"!][!//
[!//
[!CODE!][!//
[!AUTOSPACING!][!//
[!INDENT "4"!][!//
    [!LOOP "node:order(PortConfigSet/PortContainer/*, 'PortNumber')"!][!//
        [!VAR "PortNumber" = "./PortNumber"!][!//
        /* #Violation: Port_PBcfg_c_REF_4 */
        [!IF "num:i($PortNumber) < num:i(10)"!][!//
            PORT_MODULE_P0[!"$PortNumber"!][!IF "$PortNumber != ecu:get('Port.MaxAvailablePortID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "8"!]/* Port[!"$PortNumber"!] */
        [!ELSE!][!//
            PORT_MODULE_P[!"$PortNumber"!][!IF "$PortNumber != ecu:get('Port.MaxAvailablePortID')"!],[!ELSE!][!WS!][!ENDIF!][!WS "8"!]/* Port[!"$PortNumber"!] */
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//
[!ENDMACRO!][!//


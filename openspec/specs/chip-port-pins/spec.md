# chip-port-pins Specification

## Purpose
Keep a chip's pin table derived from its `ecu_resources.Port` data, and keep the Port and Dio mapping consistent with it and with the vendor Port definition.

## Requirements

### Requirement: Pin Table Derived From ECU Resources
The system SHALL derive a chip's pin table from `ecu_resources.Port`: ports `P<NN>` from `Port.AvailablePortsID`, pins `<port>_<pin>` from `Port.Port<N>_AvailablePins` with default direction INPUT, and each pin's functions from `Port.InputModesXDM<hex>` then `Port.OutputModesXDM<hex>` (`<hex>` = port × 16 + pin, lower-case), input names only for ports in `Port.AvailableReadOnlyPorts`.

#### Scenario: Ports and pins with gaps
- **WHEN** `Port.AvailablePortsID` is `_0_ _10_` and `Port.Port10_AvailablePins` lists 0 to 11 and 13 to 15
- **THEN** the pin table has ports `P00` and `P10`, and `P10` holds `P10_0` to `P10_11` and `P10_13` to `P10_15` with those pin numbers

#### Scenario: Alternate functions from the hexadecimal key
- **WHEN** `Port.InputModesXDMa0` is `GPIO CAN00_RXDH` and `Port.OutputModesXDMa0` is `GPIO CAN00_TXD`
- **THEN** pin `P10_0` has the alternate functions `GPIO`, `CAN00_RXDH`, `CAN00_TXD`

#### Scenario: Read-only port
- **WHEN** port 40 is listed in `Port.AvailableReadOnlyPorts`
- **THEN** the pins of `P40` list only input function names

#### Scenario: No Port data
- **WHEN** the ECU resources have no `Port.AvailablePortsID`
- **THEN** no pin table is derived

### Requirement: Real Port And Pin Numbers In Hardware Mapping
The hardware mapping SHALL take a port's number from the digits ending its name, and from the letters A to P (A = 0) for names ending in one of those letters, and SHALL compute `PortPinId` and the Dio channel ID as port number × 16 + the pin's own number, creating one Port pin container per existing pin.

#### Scenario: Port with a missing pin
- **WHEN** port `P10` has no pin 12 and the Port and Dio modules are mapped
- **THEN** pin `P10_13` gets `PortPinId` 173 and Dio channel ID 173, and no container is created for pin 12

#### Scenario: Distinct ports
- **WHEN** a chip has ports `P00` and `P10`
- **THEN** pin 0 of `P00` gets ID 0 and pin 0 of `P10` gets ID 160

#### Scenario: Letter-named ports keep their numbers
- **WHEN** a chip uses ports `PORT_A` and `PORT_B` with pins 0 to 15
- **THEN** the `PortPinId` values are the same as before this change, and pin 1 of `PORT_B` gets Dio channel ID 17 (before this change Dio pins carried no port number and every Dio channel ID was invalid)

### Requirement: Designer Generates The Pin Table From ECU Resources
The chip designer's pinout page SHALL offer to replace the pin table with the one derived from the chip's ECU resources. When the current pin table is not empty and differs from the derived one, the designer SHALL state how many ports and pins will be replaced and SHALL change nothing unless the user confirms; the default answer SHALL be No.

#### Scenario: Confirmed replacement
- **WHEN** the pin table holds demo ports `PORT_A` and `PORT_B` and the user confirms
- **THEN** the pin table holds the derived `P<NN>` ports and pins

#### Scenario: Declined replacement
- **WHEN** the user answers No
- **THEN** the pin table is unchanged

#### Scenario: Empty pin table
- **WHEN** the pin table is empty
- **THEN** the derived pin table is applied without asking

### Requirement: Pin Table Consistency Warning
The designer and the project diagnostics SHALL warn when the set of port numbers in the pin table differs from `Port.AvailablePortsID`, naming the missing and the extra ports, and SHALL NOT block saving or generation.

#### Scenario: Demo pin table
- **WHEN** the pin table has ports `PORT_A` to `PORT_D` and `Port.AvailablePortsID` lists 23 ports
- **THEN** a warning lists the ports missing from the pin table and the extra ones, and saving still succeeds

#### Scenario: Matching pin table
- **WHEN** the pin table was derived from the same ECU resources
- **THEN** no pin table warning is shown

### Requirement: Built-in Chips Use Vendor Pin Data
The pin table of each built-in chip SHALL equal the pin table derived from its own ECU resources.

#### Scenario: Built-in chip pin table
- **WHEN** a built-in chip YAML is loaded
- **THEN** its pin table equals the pin table derived from its `ecu_resources`, and its checksum matches its content

### Requirement: Port Mapping Writes Only What The Vendor Definition Allows
The Port mapping rule SHALL write only parameters that exist in the Port module definition and, for an enumeration whose literals the definition lists, only values among those literals. In particular it SHALL NOT write `PortPinMode`, whose only value `PORT_PIN_MODE_ALL` is the definition's default.

#### Scenario: Pin mode not written
- **WHEN** the Port module is mapped for any chip
- **THEN** no action sets `PortPinMode`

#### Scenario: Rule agrees with the vendor definition
- **WHEN** the parameters and enumeration values of the Port rule are compared with the vendor Port definition
- **THEN** every parameter exists in the definition and every enumeration value is one of the literals the definition lists

### Requirement: Initial Pin Mode Left To The Definition
The Port mapping SHALL NOT set `PortPinInitialMode`, so that each pin keeps the definition's default; the functions a pin can select are the definition's per-pin range, offered by the configuration editor, not chosen by the mapping.

#### Scenario: Mapped pin keeps the default
- **WHEN** pin `P10_13` of THA6412 is mapped
- **THEN** its container is created with `PortPinId` 173 and no action sets `PortPinInitialMode`

### Requirement: Port Page Offers No Inoperative Options
The hardware mapping wizard's Port page SHALL NOT offer a default pin mode or a default pin direction, because the mapping applies neither.

#### Scenario: Options of the Port page
- **WHEN** the options of the Port rule's page are listed
- **THEN** they include neither a default mode nor a default direction

### Requirement: Port Configuration Templates Do Not Set PortPinMode
The GPIO input and GPIO output configuration templates of the Port module SHALL NOT set `PortPinMode`, neither as a fixed nor as an adjustable parameter.

#### Scenario: Templates
- **WHEN** the Port templates `port_gpio_input` and `port_gpio_output` are loaded
- **THEN** `PortPinMode` is not among their fixed or adjustable parameters

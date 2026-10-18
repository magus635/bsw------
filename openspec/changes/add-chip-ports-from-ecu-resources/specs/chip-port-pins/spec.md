## ADDED Requirements

### Requirement: Pin Table Derived From ECU Resources
The system SHALL derive a chip's pin table from `ecu_resources.Port`: one port for each number in `Port.AvailablePortsID`, named `P` followed by the port number written with two digits, holding one pin for each number in `Port.Port<N>_AvailablePins`, named `<port>_<pin number>`, with default direction INPUT. A pin's alternate functions SHALL be the names in `Port.InputModesXDM<hex>` followed by those in `Port.OutputModesXDM<hex>` not already listed, where `<hex>` is the lower-case hexadecimal of port number × 16 + pin number. Pins of ports listed in `Port.AvailableReadOnlyPorts` SHALL get only the input function names.

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
- **THEN** the `PortPinId` values and Dio actions are the same as before this change

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

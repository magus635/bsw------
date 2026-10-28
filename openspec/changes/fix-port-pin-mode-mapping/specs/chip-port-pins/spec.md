## ADDED Requirements

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

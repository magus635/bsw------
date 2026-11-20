## ADDED Requirements

### Requirement: Peripheral Instances In Chip YAML
A chip YAML SHALL describe peripheral instances in a `resources` section mapping a resource type to a list of instances, each with a non-empty `resource_id` unique within its type, an optional `display_name` and a mapping of properties whose values are scalars or lists of scalars. Any resource type SHALL be accepted.

#### Scenario: Any peripheral type
- **WHEN** a chip YAML lists `gpt_channel` instances `GPT0` and `GPT1` with property `channel_id`
- **THEN** the loaded chip has two `gpt_channel` instances with those properties

#### Scenario: Invalid instance
- **WHEN** two `can_controller` instances share the `resource_id` `CAN0`, or a property holds a nested list
- **THEN** loading fails with an error naming the file, the resource type and the instance

#### Scenario: Lossless round trip
- **WHEN** a chip with instances of several types, each with its own properties, is saved and loaded again
- **THEN** every instance and property is identical

### Requirement: Legacy Peripheral Fields Are Migrated
Loading a chip YAML with the legacy sections `can_resources`, `adc_resources`, `spi_resources` or `intc_sources` SHALL convert them into `resources` with the types `can_controller`, `adc_unit`, `spi_unit` and `intc_source` and the property names used by the existing conversion, and saving SHALL write only `resources`. Code that builds a chip with the legacy fields SHALL keep working through the chip's effective resources.

#### Scenario: Old and new format are equivalent
- **WHEN** the same chip is described once with `can_resources` and once with `resources.can_controller`
- **THEN** both load to the same effective resources

#### Scenario: Saving writes the new format
- **WHEN** a chip loaded from the legacy format is saved
- **THEN** the YAML contains `resources` and none of the legacy sections

#### Scenario: Both present
- **WHEN** a YAML has `resources.can_controller` and also `can_resources`
- **THEN** the `resources` instances are used and a warning names the ignored legacy section

### Requirement: Designer Edits Peripheral Instances Of Any Type
The chip designer SHALL let the user add and remove resource types, add, copy and remove instances, add and remove properties, and edit each instance's properties independently, offering the resource types of the hardware mapping rules and accepting other types.

#### Scenario: Per-instance properties are kept
- **WHEN** `CAN0` has `supports_fd: true`, `CAN1` has `supports_fd: false`, and the chip is saved and opened again
- **THEN** each controller keeps its own value

#### Scenario: Batch add with numbering
- **WHEN** the user adds six `can_controller` instances with prefix `CAN` starting at 0
- **THEN** instances `CAN0` to `CAN5` exist with `controller_id` 0 to 5

#### Scenario: Property a rule needs is missing
- **WHEN** a `gpt_channel` instance has no `channel_id` and the Gpt mapping rule reads `resource.properties.channel_id`
- **THEN** the designer marks the instance and states that the hardware mapping wizard will not get `channel_id`

### Requirement: Hardware Mapping Wizard Uses The Project's Chip
When a project is open, the hardware mapping wizard SHALL take its chip from the project's own chip copy, or from the chip library when the project has none, SHALL select the project's chip by default, and SHALL map the chip's effective resources and pins.

#### Scenario: Chip only in the project
- **WHEN** the project's selected chip exists only in the project's `chips/` directory
- **THEN** the wizard offers it, selects it, and maps its peripherals

#### Scenario: Existing mappings unchanged
- **WHEN** the wizard maps a built-in chip after its YAML was migrated to `resources`
- **THEN** the CAN, ADC, SPI, Port, Dio and Intc mapping actions are the same as before the migration

#### Scenario: New peripheral type reaches its rule
- **WHEN** a chip has `gpt_channel` instances
- **THEN** the Gpt mapping rule produces mapping actions for them

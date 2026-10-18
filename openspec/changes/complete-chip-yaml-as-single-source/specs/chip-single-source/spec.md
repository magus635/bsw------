## ADDED Requirements

### Requirement: UI Constraints From The Same Resources
When a project is open, the chip constraints used to evaluate `ecu:get` and `ecu:list` in module definitions SHALL be taken from `project.ecu_resources`, the same data used for code generation, and the list of selectable chips SHALL combine the chip library, the project's `chips/` directory and the chip names of the project's resource `.properties` files.

#### Scenario: Project with only chip YAML
- **WHEN** a project has no `.properties` files and its selected chip's YAML defines `OsResource.NumOfCores` as `4`
- **THEN** a definition range `MAX = ecu:get('OsResource.NumOfCores')` evaluates to `4` in the user interface

#### Scenario: Existing project keeps its constraints
- **WHEN** `test_import_project`, which has only `.properties` chip data, is opened
- **THEN** every constraint computed before this change is present for each chip with the same value
- **AND** the only additional keys come from non-resource `.properties` files (build configurations) that code generation already reads

### Requirement: Chip Selectors Declared In Chip YAML
A chip YAML SHALL be able to declare, in a `selectors` section, the value of each selector parameter of a module definition (keyed `<Module>.<parameter>`), and the enumeration values of such a parameter SHALL be the values in its definition together with the values declared by all chips in the library, without changing the parameter's default.

#### Scenario: New chip without editing definitions
- **WHEN** a chip `THA6999_BGA100` declares `Resource.ResourceSubderivative: THA6999_BGA100` and `Resource.xdm` is loaded
- **THEN** `THA6999_BGA100` is a selectable value of `ResourceSubderivative`, the values written in `Resource.xdm` are still selectable, and the default value is unchanged

#### Scenario: Os selector with its own naming
- **WHEN** chip `THA6412_BGA516` declares `Os.OsResourceSubderivative: Os_THA6412`
- **THEN** `Os_THA6412` is a selectable value of `OsResourceSubderivative`

#### Scenario: Configured selector differs from the chip
- **WHEN** the selected chip declares `Resource.ResourceSubderivative: THA6412_BGA516` and the project's configuration has `THA6206_LFBGA292`
- **THEN** a diagnostic warning names the parameter, the configured value and the declared value, and the configuration is not changed

### Requirement: ECU Resources Prevail Over Typed Fields
For each entry of a declared mapping between the designer's typed fields and `ecu_resources` keys, the designer SHALL report a difference when the chip's `ecu_resources` contains the key and its value disagrees with the typed field, and SHALL offer to overwrite the typed fields with the `ecu_resources` values. Export and generation SHALL use only `ecu_resources`.

#### Scenario: Core count differs
- **WHEN** `metadata.cores.count` is `2` and `ecu_resources` has `OsResource.NumOfCores: 4`
- **THEN** the designer reports the difference, and overwriting sets the core count field to `4`

#### Scenario: Key absent
- **WHEN** `ecu_resources` has no core count key
- **THEN** no difference is reported for the core count

#### Scenario: Os master core notation
- **WHEN** `metadata.cores.master` is `CORE0` and `OsResource.MasterCore` is `OS_CORE_ID_0`
- **THEN** no difference is reported

### Requirement: Chip Data Version And Checksum
The designer SHALL write a `checksum` computed over the chip's normalized content when saving a chip; loading a chip whose content does not match its checksum SHALL mark it as modified and report it while still loading it; a project SHALL record the name, `resource_version` and checksum of its chip data and report, when opened, a project copy that no longer matches the record and a library chip whose checksum differs from the project copy.

#### Scenario: Edited outside the designer
- **WHEN** a value in a saved chip YAML is changed by hand
- **THEN** loading the chip reports that its content was modified and the chip is still available

#### Scenario: Project copy modified
- **WHEN** the project's `chips/<chip>.yaml` is changed after the project recorded its checksum
- **THEN** opening the project reports that the project's chip data was modified

#### Scenario: Newer library version
- **WHEN** the library's chip has a different checksum from the project's copy
- **THEN** opening the project reports it and points to "Update from Library"

#### Scenario: Old chip without checksum
- **WHEN** a chip YAML has no `checksum`
- **THEN** it loads without any modification report

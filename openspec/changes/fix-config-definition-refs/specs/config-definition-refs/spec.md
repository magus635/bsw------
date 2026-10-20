## ADDED Requirements

### Requirement: Absolute Definition References
Every `DEFINITION-REF` the tool writes into a module configuration file SHALL be the absolute path of the definition element in its definition file, `/<AR-PACKAGE>/<Module>/...`, where `/<AR-PACKAGE>/<Module>` is the module's actual path in the loaded definition (for an XDM definition, its AR-PACKAGE and MODULE-DEF names).

#### Scenario: New parameter value of an XDM module
- **WHEN** the Os definition is `Os.xdm` with AR-PACKAGE `THA6_ASR21` and the user sets the unset parameter `OsOS/OsVendorArtiTraceTask` and saves
- **THEN** the saved parameter value has `DEFINITION-REF` `/THA6_ASR21/Os/OsOS/OsVendorArtiTraceTask`

#### Scenario: New container instance
- **WHEN** the user creates a `CanController` instance in `CanConfigSet` of a Can module whose definition path is `/THA6_AS440_FuSa/Can` and saves
- **THEN** the saved container has `DEFINITION-REF` `/THA6_AS440_FuSa/Can/CanConfigSet/CanController`

#### Scenario: New module configuration
- **WHEN** the tool creates the configuration of a module whose definition path is `/THA6_AS440_FuSa/Port` and saves it
- **THEN** the module configuration's `DEFINITION-REF` is `/THA6_AS440_FuSa/Port`

### Requirement: Specific Definition Types
The `DEST` attribute of each `DEFINITION-REF` the tool writes SHALL be the type of the definition element: the parameter's definition type (for example `ECUC-BOOLEAN-PARAM-DEF`), `ECUC-REFERENCE-DEF` or `ECUC-CHOICE-REFERENCE-DEF` for references, and `ECUC-PARAM-CONF-CONTAINER-DEF` or `ECUC-CHOICE-CONTAINER-DEF` for containers.

#### Scenario: New boolean parameter
- **WHEN** the user sets a BOOLEAN parameter that was not configured and saves
- **THEN** the saved parameter value has `DEST="ECUC-BOOLEAN-PARAM-DEF"`

### Requirement: Repair On Load
When a module configuration is loaded, the tool SHALL correct definition references that are relative, that use a module path other than the definition's actual path, or whose `DEST` is the generic `ECUC-PARAMETER-DEF`, SHALL report the number of corrections in the log, and SHALL write the corrected references on the next save. Values whose references are already correct SHALL be left unchanged.

#### Scenario: Saved project with relative references
- **WHEN** a configuration file contains `<DEFINITION-REF DEST="ECUC-PARAMETER-DEF">OsOS/OsVendorArtiTraceTask</DEFINITION-REF>` and the project is loaded and saved
- **THEN** the saved file contains `<DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/THA6_ASR21/Os/OsOS/OsVendorArtiTraceTask</DEFINITION-REF>`

#### Scenario: Values imported from EB are unchanged
- **WHEN** a configuration file holds only references written by EB tresos and the project is loaded and saved
- **THEN** every `DEFINITION-REF` and `DEST` in the saved file is unchanged

#### Scenario: Generation is unchanged
- **WHEN** a project is generated before and after its configuration references are corrected
- **THEN** the generated files are identical

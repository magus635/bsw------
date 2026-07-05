# eb-value-import — Delta

## ADDED Requirements

### Requirement: Lossless Preservation of Unknown Parameters

Parameters present in an imported value file but absent from the module definition SHALL be preserved through the full edit/save cycle: they SHALL be serialized back into the saved configuration file verbatim, and the UI SHALL display a per-container warning identifying them. They SHALL NOT be silently discarded.

#### Scenario: Save after import preserves unknown parameters

- **WHEN** an EPC file containing a parameter not present in the loaded definition is imported and the project is saved
- **THEN** the saved config ARXML still contains that parameter value
- **AND** re-opening the project shows it again under the same container

#### Scenario: User visibility

- **WHEN** a container holds unknown parameters
- **THEN** the configuration UI marks the container with a warning listing the unrecognized parameter names

### Requirement: Standalone Value File Import

The tool SHALL allow importing a single EB value file (.epc/.arxml/.xdm) into an already-loaded module, replacing that module's configuration — the import counterpart of EPC export. The user SHALL be warned that the current configuration and undo history will be replaced, and the file SHALL be rejected with a clear message when it contains no configuration for the target module. Provenance (`origin: eb-import`, source path, timestamp) SHALL be recorded.

#### Scenario: Import EPC into a loaded module

- **WHEN** a module with a loaded definition is selected and the user imports a matching .epc file
- **THEN** the module's configuration is replaced by the file contents (with normalization and unknown-parameter flagging applied)
- **AND** cross-module references are re-resolved and the tree view refreshed

#### Scenario: File does not contain the module

- **WHEN** the selected value file contains configurations only for other modules
- **THEN** the import is rejected with a message listing the modules the file does contain

### Requirement: Multi-Module Value Files

Value file parsing SHALL process every `ECUC-MODULE-CONFIGURATION-VALUES` element in a file. During EB project import, each configuration SHALL be matched to its module by short-name; configurations with no matching definition SHALL load as stub modules.

#### Scenario: EPC file with two module configurations

- **WHEN** an imported EPC file contains configurations for two modules
- **THEN** both modules receive their configuration values

### Requirement: Exact Definition Reference Resolution

Instance-named DEFINITION-REF values in imported files SHALL be resolved by walking the definition hierarchy level-by-level, constraining candidates at each level to the parent container definition's sub-containers. Heuristic (score-based) matching SHALL be used only when exact resolution fails, and every heuristic remap SHALL be logged with the original and remapped path.

#### Scenario: Instance-named ref resolved structurally

- **WHEN** an imported container has DEFINITION-REF `/Vendor/Os/OsCounter_Software` and its parent's definition has a sub-container `OsCounter`
- **THEN** the ref is remapped to the `OsCounter` definition without invoking heuristic scoring

#### Scenario: Heuristic fallback is auditable

- **WHEN** exact resolution fails and a heuristic match is applied
- **THEN** a warning log records the container, the original ref, and the chosen definition

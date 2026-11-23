## ADDED Requirements

### Requirement: Multi-Variant SIP Partitioning And Implementation Attribution

When scanning multi-variant SIP modules, `SipScanner` SHALL resolve `BSW-IMPLEMENTATION` ownership from `VENDOR-SPECIFIC-MODULE-DEF-REF` before falling back to `SHORT-NAME` suffix stripping, and `partition_module_files` SHALL route each fragment exclusively to its matching `ECUC-MODULE-DEF` partition rather than broadcasting unmatched fragments across all variants.

#### Scenario: Infixed BSW-IMPLEMENTATION MemMap attribution via VENDOR-SPECIFIC-MODULE-DEF-REF

- **WHEN** `Components/CanTrcv_30_Tle9255/BSWMD/CanTrcv_30_Tle9255_MemMap.arxml` contains only a `BSW-IMPLEMENTATION` named `CanTrcv_30_Tle9255_Impl` with `VENDOR-SPECIFIC-MODULE-DEF-REF` `/MICROSAR/CanTrcv_Tle9255/CanTrcv`
- **THEN** `SipScanner` assigns that file to module `CanTrcv` and `partition_module_files` routes it exclusively into the `CanTrcv_Tle9255` package partition
- **AND** its `MEMORY-SECTIONS` are merged into `CanTrcv_Tle9255` and are not lost as an orphan definition-less module

#### Scenario: Unmatched variant fragments are not broadcast across partitions

- **WHEN** `CanTrcv` has two definition partitions (`/MICROSAR/CanTrcv_GenericCan/CanTrcv` and `/MICROSAR/CanTrcv_Tle9255/CanTrcv`) and an unmatched config or implementation fragment targets a third definition path `/MICROSAR/CanTrcv_Other/CanTrcv`
- **THEN** `partition_module_files` SHALL NOT copy that fragment into the `CanTrcv_GenericCan` or `CanTrcv_Tle9255` partitions

### Requirement: Definition-Exact Config Extraction, Restore, And Upgrade

Configuration extraction (`_extract_module_config`, `load_configuration`), deleted-module restoration (`restore_deleted_module`), and Format 8 project upgrade (`upgrade_to_v8`) SHALL bind modules by exact `DEFINITION-REF` when available and SHALL NOT silently select or merge sibling implementation variants that happen to share the same module `SHORT-NAME`.

#### Scenario: Delete and restore CanTrcv_Tle9255 when CanTrcv_GenericCan also exists

- **WHEN** a Format 8 project has libraries containing both `CanTrcv_GenericCan` (`/MICROSAR/CanTrcv_GenericCan/CanTrcv`) and `CanTrcv_Tle9255` (`/MICROSAR/CanTrcv_Tle9255/CanTrcv`), and the user deletes `CanTrcv` (bound to `CanTrcv_Tle9255`) and restores it from `.history/deleted/`
- **THEN** `restore_deleted_module` reads the archive's `DEFINITION-REF` and restores the module using the `CanTrcv_Tle9255` package, preserving `CanTrcvBaudrateRatio`

#### Scenario: Reject ambiguous archive without DEFINITION-REF when multiple variants exist

- **WHEN** an archived or legacy configuration lacks a specific `DEFINITION-REF` (or uses only `/AUTOSAR/EcucDefs/CanTrcv`) while multiple variant packages provide `CanTrcv`
- **THEN** `restore_deleted_module` raises an error listing the candidate variant definitions instead of silently picking the alphabetically first package

#### Scenario: Single file containing multiple variant configuration blocks

- **WHEN** an ARXML value file contains configuration blocks for both `/MICROSAR/CanTrcv_GenericCan/CanTrcv` and `/MICROSAR/CanTrcv_Tle9255/CanTrcv` and the target definition path is `/MICROSAR/CanTrcv_Tle9255/CanTrcv`
- **THEN** extraction/loading selects only the `/MICROSAR/CanTrcv_Tle9255/CanTrcv` block and does not merge parameters from `/MICROSAR/CanTrcv_GenericCan/CanTrcv`

### Requirement: Controlled Module Variant Switching

The workspace project SHALL allow switching an active module from its current implementation variant package to another variant package sharing the same module `SHORT-NAME` via a previewable, atomic operation (`switch_module_variant`), reporting kept items, incompatible/unknown parameters, newly required containers/parameters, and baseline merge effects before applying, and rolling back completely on error or rejection.

#### Scenario: Preview compatibility before switching module variant

- **WHEN** `switch_module_variant("CanTrcv", target_pkg, lib_index, preview_only=True)` is called to switch from `CanTrcv_Tle9255` to `CanTrcv_GenericCan`
- **THEN** the returned `VariantSwitchPlan` reports `CanTrcvBaudrateRatio` as incompatible/moved-to-unknown, `CanTrcvHwInterface` as newly required, and leaves the active project configuration unmodified

#### Scenario: Atomic variant switch rolls back on error

- **WHEN** applying `switch_module_variant` fails during definition parsing, baseline reconciliation, or confirmation rejection
- **THEN** the original `module_def`, `ModuleEntry.definition`, `packages`, configuration values, and baseline snapshot are restored intact

### Requirement: Variant-Aware Module Selection UI

`IntegrationWizard`, `DaVinciTreeView`, and `ProjectPropertiesDialog` SHALL distinguish sibling module implementation variants by their definition path and package identity, prevent selecting multiple variants of the same module simultaneously, and allow switching an installed module's variant from the UI.

#### Scenario: Distinguish sibling variants and report exact installation status

- **WHEN** libraries provide `CanTrcv_GenericCan` and `CanTrcv_Tle9255` and the project already has `CanTrcv_Tle9255` installed
- **THEN** `IntegrationWizard` displays the variant/definition path for each candidate, searches match both definition path and package directory name, marks `CanTrcv_Tle9255` as `Installed`, and marks `CanTrcv_GenericCan` as `Other Variant` (not `Installed`)

#### Scenario: Enforce mutual exclusion across variants of the same module in IntegrationWizard

- **WHEN** both `CanTrcv_GenericCan` and `CanTrcv_Tle9255` are available in `IntegrationWizard` and the user checks `CanTrcv_Tle9255` (or runs `Select All Compatible`)
- **THEN** sibling variants of `CanTrcv` cannot remain simultaneously checked, and `Select All Compatible` skips un-installed multi-variant modules with multiple candidates

#### Scenario: Display active variant definition path in project views

- **WHEN** a project contains a module bound to `/MICROSAR/CanTrcv_Tle9255/CanTrcv`
- **THEN** `DaVinciTreeView` displays the variant identity and full definition path in the module node label/tooltip, `ProjectPropertiesDialog` lists the module's bound definition path, and the module context menu offers a variant-switch action when alternative variants exist in registered libraries

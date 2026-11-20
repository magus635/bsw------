# project-file — Delta

## ADDED Requirements

### Requirement: EB Import Mode Selection

EB Tresos project import SHALL offer two modes: **copy** (self-contained: plugin directories are copied into the project's `Def/plugins/` and `generate_PB` templates into `templates/`) and **link** (definitions and templates are resolved from the original EB source tree via the recorded `eb_source_root`, with the `TRESOS_PLUGINS_PATH` environment variable as fallback). The selected mode SHALL be persisted in the `.dpa` file. Copy SHALL be the default mode.

#### Scenario: Copy mode produces a self-contained project

- **WHEN** a user imports an EB project in copy mode and relocates the project directory
- **THEN** the project opens with all definitions, resources, and templates resolved from inside the project tree

#### Scenario: Link mode avoids duplication

- **WHEN** a user imports an EB project in link mode
- **THEN** no plugin directories are copied into the project
- **AND** definitions and templates resolve against the original EB tree

#### Scenario: Link mode with missing source tree

- **WHEN** a link-mode project is opened and `eb_source_root` does not exist and `TRESOS_PLUGINS_PATH` does not resolve the plugins
- **THEN** loading reports a clear "EB source tree not found" error naming the expected path, instead of failing per-module with cryptic errors

### Requirement: Module Provenance Metadata

The `.dpa` project file (format version 7) SHALL record, for each module, its origin (`native` or `eb-import`), the source EPC path relative to `eb_source_root` when applicable, and the import timestamp. `eb_source_root` SHALL be stored relative to the project root whenever the source tree lies inside it.

#### Scenario: Provenance recorded on EB import

- **WHEN** a module is loaded from an EPC file during EB project import
- **THEN** after saving, its `.dpa` entry contains `origin: "eb-import"`, the relative `source_epc` path, and `imported_at`

#### Scenario: Backward-compatible load of v6 projects

- **WHEN** a `.dpa` file with `format_version` 6 or lower is opened
- **THEN** the project loads without error and missing provenance fields default to `origin: "native"`
- **AND** re-saving writes format version 7

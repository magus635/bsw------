## ADDED Requirements

### Requirement: Vector SIP Library Ingestion

The system SHALL provide a command-line tool to convert a Vector MICROSAR SIP directory into module packages compatible with Phase 1 (module.json + config/ format).

#### Scenario: Ingest vBRS module from SIP

- **WHEN** user runs `python -m autosar_configurator.tools.ingest_sip --sip-root D:\davinci\mcuapp --output-dir D:\prj\sip_lib --derivative-uuid B632B9EE-F23D-43CD-9C54-542178A058D9`
- **THEN** the tool scans `Components/vBRS/BSWMD/` and `DemoComponents/vBaseEnv/BSWMD/` for vBRS files
- **AND** merges `vBRS_bswmd.arxml` + `vBRS_General_pre.arxml` + `Tongxin_THA6/vBRS_THA6_pre.arxml` by AUTOSAR path
- **AND** creates `D:\prj\sip_lib\vBRS/module.json` and `D:\prj\sip_lib\vBRS/config/` with merged definitions and Pre/Rec values
- **AND** records each source file in a `sources.json` with file paths and SW-VERSION

#### Scenario: Merge conflict detection

- **WHEN** two files declare `/MICROSAR/Arti_Impl` with different `SW-VERSION` values (same single-value field)
- **THEN** the tool raises `SipMergeError` naming the path, both files, and the conflict

#### Scenario: Derivative subdirectory selection with mapping

- **WHEN** the tool processes Os module which has `GeneratorMsr/DerivativeMapping_Os.xml` mapping UUID `B632B9EE-...` to `SIP_Folder = Generic_CortexR52_ASIMD`
- **AND** the derivative is `Tongxin_THA6206` (UUID `B632B9EE-...`)
- **THEN** the tool loads only `Components/Os/BSWMD/Os/Generic_CortexR52_ASIMD/*_pre.arxml` and `*_rec.arxml`
- **AND** skips the other 41 Os subdirectories

#### Scenario: Derivative subdirectory selection without mapping

- **WHEN** a component (e.g., vBaseEnv) has subdirectories but no `DerivativeMapping_*.xml`
- **THEN** the tool loads all subdirectories (all pre/rec files in all subdirs for that component)

#### Scenario: Cross-component module fragments

- **WHEN** vLinkGen is split across `Components/vLinkGen/BSWMD/` and `DemoComponents/vBaseEnv/BSWMD/Tongxin_THA6/`
- **THEN** the tool merges all files declaring `/MICROSAR/vLinkGen_Pre` by path, regardless of directory
- **AND** lists all 9 source files in `sources.json`

### Requirement: BSWMD Element Merging

The system SHALL merge elements from multiple ARXML files by AUTOSAR path and element type.

#### Scenario: Merge IMPL + MemMap for same module

- **WHEN** two files declare `/MICROSAR/Arti_Impl` (`Arti_bswmd.arxml` declares BSW-IMPLEMENTATION version/pre-ref; `Arti_MemMap.arxml` declares MEMORY-SECTION children)
- **THEN** the resulting element has both the IMPL fields and the MEMORY-SECTION children from both files
- **AND** the merged element is a valid `ECUC-MODULE-DEF`

#### Scenario: Extract BSW-IMPLEMENTATION metadata

- **WHEN** merging a module, the system locates the `BSW-IMPLEMENTATION` child
- **THEN** the tool extracts and preserves: `SW-VERSION`, `AR-RELEASE-VERSION`, `VENDOR-NAME`, `MEMORY-SECTIONS`, `REQUIRED-ARTIFACTS`, `PRECONFIGURED-CONFIGURATION-REFS`, `RECOMMENDED-CONFIGURATION-REFS`

### Requirement: Conflict Detection and Reporting

The system SHALL detect and report merge conflicts without silent overwrite.

#### Scenario: Type conflict

- **WHEN** one file declares `/MICROSAR/Arti_Impl` as `ECUC-MODULE-DEF` and another as `BSW-IMPLEMENTATION`
- **THEN** the tool raises `SipMergeError` with paths to both files

#### Scenario: Single-value field conflict

- **WHEN** two files declare `/MICROSAR/Arti_Impl/SW-VERSION` with different values (e.g., "1.02.00" vs "1.03.00")
- **THEN** the tool raises `SipMergeError` naming the field, path, both values, and both files

#### Scenario: Duplicate module definition across components

- **WHEN** two components declare `ECUC-MODULE-DEF` at the same AUTOSAR path (e.g., both `/MICROSAR/EcuC`)
- **THEN** the tool raises `SipMergeError` (two definitions of one module are not allowed, even with same content)

### Requirement: Module Package Generation

The system SHALL write the merged definitions and Pre/Rec values into a Phase 1 module package.

#### Scenario: Write module.json + config/define.arxml

- **WHEN** vBRS has been merged and contains 1 `ECUC-MODULE-DEF` and 1 Pre config
- **THEN** the tool writes `module.json` with name, type="bswmd", optional impl fields, and chip/variant mappings
- **AND** writes `config/define.arxml` containing the merged AUTOSAR definition
- **AND** writes `config/pre/<Module>_Pre.arxml` containing the Pre configuration values

### Requirement: Reference Validation (Non-blocking)

The system SHALL warn if Pre/Rec references do not resolve, but not block ingestion.

#### Scenario: Missing Pre/Rec reference

- **WHEN** a module's `PRECONFIGURED-CONFIGURATION-REF` points to `/MICROSAR/Arti_Pre` but no `ECUC-MODULE-CONFIGURATION-VALUES` with that path is found in the ingested files
- **THEN** the tool logs a warning: "Unresolved reference `/MICROSAR/Arti_Pre` from `/MICROSAR/Arti_Impl`"
- **AND** continues ingestion (does not raise error)

### Requirement: Ingestion Progress and Reporting

The system SHALL report what was ingested and any issues encountered.

#### Scenario: Ingestion summary

- **WHEN** ingestion completes
- **THEN** the tool writes a report listing:
  - Number of components scanned
  - Number of ARXML files processed
  - Number of modules merged
  - Number of conflicts (if any) and whether ingestion stopped or continued with warnings
  - Module source file manifest

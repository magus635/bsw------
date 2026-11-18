# Vector SIP Library, DaVinci Import, and MCAL Resource Enhancement

## Why

Users need to migrate existing DaVinci Configurator projects to this tool to achieve full independence from Vector tooling. Currently:

1. **No Vector SIP support**: The tool cannot understand Vector MICROSAR SIP layout (Components/*/BSWMD/), which contains 110+ BSW modules with definitions split across multiple ARXML files (e.g., `Arti_bswmd.arxml` + `Arti_MemMap.arxml`).

2. **No DaVinci import**: Users cannot migrate their 28+ module configurations from existing DaVinci XML `.dpa` projects, forcing manual recreation of all configuration values.

3. **Incomplete MCAL resources**: Port module ECU resources (AvailableEXTIModule, AvailableGTMModule, AvailableIOMPINModule, AvailablePSI5Module, AvailablePortsID) are missing, causing 14 warnings on startup and preventing correct Port configuration.

These three problems block the "replace DaVinci Configurator" goal. The design documents (SIP spec R1-R6, Integration design §6.10, §8) have defined the solution architecture.

## What Changes

### 1. Vector SIP Library One-Time Ingestion Tool

Create a command-line tool to convert Vector MICROSAR SIP into module packages:

- Scan `D:\davinci\mcuapp\Components\*/BSWMD\` and `DemoComponents\*/BSWMD\`
- Merge same-path AUTOSAR elements across files (e.g., `/MICROSAR/Arti_Impl` from 2 files)
- Handle derivative-specific subdirectories (42 Os subdirs → select one via `DerivativeMapping_Os.xml` UUID)
- Extract `BSW-IMPLEMENTATION`, `MEMORY-SECTIONS`, Pre/Rec configuration values
- Generate `module.json` + `config/` module packages (Phase 1 format)
- Detect conflicts (same path different types, same single-value field different values)

### 2. DaVinci Project Import

Implement `WorkspaceManager.import_davinci_project()`:

- Parse DaVinci XML `.dpa` (`<ProjectAssistant>` format)
- Extract metadata: `<SIP>`, `<Derivative>` (UUID + name), `<Folders>`, `<ECUC><Active>`
- Import 28 BSW module configurations from DaVinci ARXMLs
- Prompt user for EB MCAL directory (e.g., `TresosMcalProject/THA6206_LFBGA292_AS440/config`)
- Import MCAL modules via existing EB import (Phase 1)
- Generate format-8 `.dpa` to user-specified new directory (preserve original DaVinci project)
- Produce import report: per-module container/parameter/reference counts, unresolved items

### 3. EB MCAL Resource Extraction

Enhance EB plugin loading to extract chip-specific ECU resources:

- Parse `autosar/<Module>_<Chip>.arxml` files (previously skipped)
- Extract Port module resources (AvailableEXTIModule, AvailableGTMModule, etc.)
- Merge into tool's chip database (`chips/<Chip>.yaml`)
- Record ARXML source for traceability (SIP spec R4)

**BREAKING**: None. All changes are additive; existing projects continue to work.

## Impact

### Affected Specs

- **NEW**: `sip-library` - Vector SIP ingestion and BSWMD merging
- **NEW**: `davinci-import` - DaVinci XML project migration
- **MODIFIED**: `mcal-resources` (if exists) or new spec - EB plugin resource extraction

### Affected Code

- `autosar_configurator/core/sip_import.py` (new) - SIP ingestion tool
- `autosar_configurator/core/workspace_manager.py` - add `import_davinci_project()`
- `autosar_configurator/core/packages/eb_plugin.py` - add `autosar/*.arxml` parsing
- `autosar_configurator/core/parser/` - may need ECUC-MULTILINE-STRING support
- `autosar_configurator/ui/controllers/project_controller.py` - add "Import DaVinci Project" menu

### User Benefits

1. **One-click migration**: Convert entire DaVinci project with 28+ modules to this tool
2. **Zero manual work**: All configuration values, definitions, and resources preserved
3. **Traceability**: Know exactly which SIP files contributed to each module
4. **Complete resources**: All 14 Port warnings resolved, chip data complete
5. **Baseline protection**: Phase 1 baseline merge protects user edits during SIP upgrades

### Dependencies

- **Required**: Phase 1 module packages, baseline merge, format-8 `.dpa` (completed)
- **Input**: `D:\davinci\mcuapp` SIP directory, user's DaVinci XML `.dpa` project
- **Output**: Format-8 project with module packages, EB MCAL config, complete chip resources

### Testing Strategy

- Unit tests: BSWMD merging, conflict detection, derivative subdirectory selection
- Integration test: Import sample DaVinci `StartApplication.dpa` (28 modules)
- Acceptance: Generated code byte-identical to DaVinci baseline (modulo timestamps)
- Verification: All 14 Port ECU resource warnings disappear after import

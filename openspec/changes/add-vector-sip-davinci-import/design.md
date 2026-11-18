# Design: Vector SIP Ingestion, DaVinci Import, MCAL Resources

## Context

Migration from DaVinci Configurator requires three connected capabilities:

1. **Vector SIP → module packages**: Convert `D:\davinci\mcuapp` (124 component dirs, 110 with BSWMD, 115 arxml in subdirectories) into the Phase 1 module package format.
2. **DaVinci project → format 8 project**: Read XML `.dpa` and its ~30 `*_ecuc.arxml` files, produce a format-8 JSON project.
3. **EB MCAL → chip resources**: Extract Port and other MCAL ECU resources from EB plugin `autosar/*.arxml`, closing 14 missing-resource warnings.

Constraints from the SIP spec (2026-11-08) and Integration design (2026-11-09):

- DaVinci project directory must remain untouched (used as comparison baseline).
- No silent data loss, no silent merge conflicts, no silent missed files.
- Module identity is the AUTOSAR definition path, not the file or directory name.
- `.dpa` manages all directories; no hardcoded directory names in code.
- MCAL uses EB plugin layout, BSW uses Vector layout.
- Ingestion is one-time; runtime only sees module packages.

## Goals / Non-Goals

**Goals**
- A CLI tool that converts a Vector SIP tree into module packages, verified against DaVinci's active configuration.
- A UI command that imports a DaVinci XML project into a format-8 project, preserving all values.
- Complete chip ECU resources extracted from EB MCAL `autosar/*.arxml` with source traceability.
- Import report that accounts for every container, parameter, reference, and every skip.

**Non-Goals**
- Code generation (MemMap, linker, templates) — later subprojects.
- Parsing SystemExtract, SWC, InternalBehavior — record paths only.
- Writing back DaVinci format.
- Modifying `D:\davinci\mcuapp` files.
- Runtime scanning of the SIP tree (the whole point of ingestion is to avoid that).

## Decisions

### D-A: Ingestion is a separate CLI tool, not a UI wizard

**Decision**: `tools/ingest_sip.py` (or `python -m autosar_configurator.tools.ingest_sip`) writes module packages to a target directory; the UI is not involved.

**Why**: Ingestion runs once per SIP version, takes minutes over hundreds of files, and its output is a directory tree the user inspects before adopting. A CLI keeps it testable headless and out of the app's startup path. The DaVinci import (D-B) consumes the packages it produces.

**Alternative considered**: Import-on-open (rejected by the Integration design §1.4 —颠覆性改动, performance, three layouts at runtime).

### D-B: DaVinci import is two stages — SIP first, then project

**Decision**: `import_davinci_project()` requires an already-ingested module library (or ingests inline if the user asks). The import maps `<SIP>` to a `vector`-layout library and reads module values from the DaVinci ECUC ARXMLs.

**Why**: The DaVinci project import needs definitions to bind `DEFINITION-REF`s. Those definitions come from the module packages. Separating ingestion lets the user verify a library once and reuse it across projects.

### D-C: Merge by AUTOSAR path, conflict = error

**Decision**: Elements merge by their AUTOSAR path (`/MICROSAR/Arti_Impl`), never by UUID. Conflicts (type mismatch, differing single-value field, duplicate `ECUC-MODULE-DEF` for one path across components) raise `SipMergeError` naming the path and both files.

**Why**: SIP spec R3. DaVinci merges in memory the same way; a silent "last file wins" would lose `Arti_MemMap.arxml`'s memory sections.

### D-D: Derivative subdirectory selection follows DerivativeMapping, load-all otherwise

**Decision**: When a component has `GeneratorMsr/DerivativeMapping_<Module>.xml`, select the one subdirectory whose UUID matches the project derivative; no match = error. Components without a mapping file load all subdirectories (as observed for vBaseEnv, vMem_30_Fls).

**Why**: SIP spec §5.2, R2. The rule is inherited verbatim from the SIP spec. "Load all" remains an inference from the sample and is validated by the value comparison (Task 2.11).

### D-E: MCAL ECU resources come from the Resource plugin's `resource/*.properties`

**Decision**: Read chip ECU resources from the EB **Resource** plugin's
`resource/CotexR52_<Chip>.properties` (e.g. `Port.AvailableEXTIModule: _1_`), not from
`autosar/<Module>_<Chip>.arxml`. Write them into `chips/<Chip>.yaml` under the existing keys — which
already carry these names with `null` values and a `待填写` note — plus a `source` field naming the file.

**Why**: Verified 2026-11-18 against the sample MCAL installation: the `Port_THA6_AS440` plugin's
`autosar/Port_THA6206_LFBGA292.arxml` holds the module *definition*; the actual Port resource values
(`AvailableEXTIModule`, `AvailableGTMModule`, `AvailablePortsID`, …) live in the sibling
`Resource_THA6_AS440` plugin's properties file. The first version of this decision named the wrong
source and would have produced an empty import. Recording `source` satisfies R4 traceability and the
existing `chip-repair` convention (chip data flagged, never deleted).

### D-F: Import report is a Markdown file plus a UI summary

**Decision**: The import writes `<history>/reports/<timestamp>_davinci_import.md` and shows a summary dialog with a link to the file. Every skipped MCAL module, unresolved reference, and dropped file is listed.

**Why**: SIP spec R6, 反目标 "不得有未报告的丢失". Reuses the Phase 1 import report pattern (`ImportReport` in `eb_import.py`).

### D-G: Pre-configuration locking applies to imported values

**Decision**: When importing BSW modules that have Pre configurations, the Pre values become PRE-owned in the baseline (Phase 1 semantics), read-only until unlocked.

**Why**: Matches DaVinci behavior (Pre is read-only) and reuses Phase 1 `compose_base`/`origin` without new machinery.

## Risks / Trade-offs

| Risk | Mitigation |
|------|------------|
| "Load all subdirectories" is an inference, not decompiled truth | Task 2.11 value-by-value comparison against DaVinci's active config; any difference is reported, not silently accepted |
| SIP ingestion is slow over 124 components | Scan once, cache by component mtime; ingestion is offline so latency is acceptable |
| A SIP upgrade changes a definition the user's config depends on | Phase 1 baseline three-way merge protects user edits; import report lists version changes (R4) |
| Port resource extraction may find resources in several chip arxml files | Merge by AUTOSAR path with conflict detection (same rule as D-C) |
| User points the import at an incomplete EB MCAL directory | Import report lists missing MCAL modules and unresolved BSW→MCAL references; user confirms |

## Migration Plan

1. Ingest the SIP once into a library directory (e.g., `D:\prj\sip_library`).
2. Import `StartApplication.dpa` into a new format-8 project, pointing at that library and at `TresosMcalProject/THA6206_LFBGA292_AS440/config`.
3. Verify: import report shows 28 modules, 0 unresolved references; the 14 Port warnings are gone.
4. Generate code and diff against the DaVinci baseline (`Config/GenData`); accept only timestamp differences.
5. Keep the DaVinci project directory as the comparison baseline; do not delete it.

Rollback: the imported project is a new directory; deleting it and reopening the DaVinci project leaves everything unchanged. No existing project is modified by this change.

## Open Questions

None blocking. Two items to confirm during implementation:
- Whether `ECUC-MULTILINE-STRING` and other definition types missing from the current parser actually appear in the sample SIP (spec R3 says they must be readable if so). Investigate in Task 1.1 and add parser support only for types that occur.
- Whether any component other than `Os` ships a `DerivativeMapping_*.xml` (spec says only Os). The scanner handles the general case regardless.

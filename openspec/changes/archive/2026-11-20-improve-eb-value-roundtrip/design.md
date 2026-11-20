# Design — improve-eb-value-roundtrip

## Context

EPC import currently flows: `load_configuration()` → `ArxmlParser.parse_ecuc_configuration_values()` (first module element only) → `_normalize_definition_refs()` (heuristic) → `_cleanup_invalid_parameters()` (quarantines to `unknown_parameters`, never persisted). Serialization (`ecuc_serializer.py`) writes only known parameters. There is no export path back to `.epc`.

## Goals / Non-Goals

- Goals: no silent data loss on import→save; all modules in a file imported; deterministic, auditable ref resolution; EB-compatible export enabling round-trip verification in EB Tresos.
- Non-Goals: POST-BUILD `VARIATION-POINT` structural parsing (separate follow-up change); editing UI for unknown parameters (display/warn only).

## Decisions

- **Unknown-parameter storage**: promote `unknown_parameters` from an ad-hoc attribute to a first-class field on `EcucContainerValue` (default empty dict). **Copy semantics, not move**: the values stay in `parameter_values`/`multi_parameter_values` (the generator's XPath engine and the serializer read from there — the MCAL_R440 oracle showed that moving them breaks Os codegen, e.g. MPU region names read by templates but absent from the vendor def). `unknown_parameters` is an index of flagged names for UI warnings.
  - Alternative considered: sidecar file for unknowns — rejected (fragments the config, breaks EB re-import).
  - Alternative considered: move semantics + teaching the XPath engine to read `unknown_parameters` — rejected (two value stores, ordering ambiguity, wider blast radius).
- **Multi-module parse**: `ArxmlParser` gains `parse_all_module_configurations(root) -> list`. `load_configuration()` keeps single-module semantics (picks the one matching the manager's module short-name, warns about the rest); `import_eb_project()` uses the full list so one file can populate several managers.
- **Exact ref resolution**: rewrite `_normalize_definition_refs()` as a top-down walk: at the module root, candidates = module def containers; at each level, candidates = resolved parent def's `sub_containers`. Exact short-name match first, then choice-container transparency, then existing scoring as fallback with a mandatory warning log.
- **EPC export**: implement in `ecuc_serializer.py` as a layout variant of the existing serializer (EB package structure, `.epc` extension, same element ordering rules as EB output). Reuse deterministic sorted() conventions already mandated by the project. Byte-determinism verified by double-export test.
- **Oracle validation**: regression harness imports `~/Desktop/ImportEB_1/MCAL_R440_FuSa`, generates via `CodeGenerator.generate_all`, and diffs against `cmpBASe/`; plus import→export→re-import semantic-equality test.

## Risks / Trade-offs

- Serializing unknown parameters may surprise strict downstream consumers → they are what EB itself produced; keeping them is strictly more correct. Mitigation: UI warning makes their presence visible.
- Exact ref-walk could regress cases the heuristic happened to fix → keep heuristic as fallback; log every fallback so regressions are diagnosable.
- EB `.epc` layout details (package nesting, UUIDs, schema header) may vary by EB version → derive the layout from the real EPC files in the MCAL_R440 reference project and lock it with round-trip tests.

## Migration Plan

No file-format break: saved configs gain extra (previously dropped) parameter values only. Rollback = revert; previously saved projects are unaffected.

## Open Questions

- Should export offer a "strip unknown parameters" option for consumers that reject them? (Default: keep.)

# Improve EB Value Import Fidelity and Add EPC Export

## Why

EPC (EB value file) import has fidelity gaps that lose data or mis-map it: (1) parameters not found in the definition are quarantined into `container.unknown_parameters` (`config_manager.py:807`) but never serialized or shown — **saving after import silently discards them**; (2) `load_configuration()` (`config_manager.py:757`) reads only the first `ECUC-MODULE-CONFIGURATION-VALUES` per file, dropping additional modules; (3) `_normalize_definition_refs()` (`config_manager.py:858`) maps instance-named DEFINITION-REFs to definitions by heuristic scoring, which can mis-map sparse containers. There is also no way to export a configuration back to an EPC file, so users cannot round-trip edits into EB Tresos for verification.

## What Changes

- **Fix data loss**: serialize `unknown_parameters` back out on save (preserved verbatim in the config ARXML) and surface them in the UI as per-container warnings.
- **Multi-module EPC files**: parse all `ECUC-MODULE-CONFIGURATION-VALUES` elements in a file; `import_eb_project` matches each to its module (by short-name), instead of taking only the first.
- **Exact DEFINITION-REF resolution**: resolve instance-named refs by walking the definition tree level-by-level (parent container def's `sub_containers` constrain candidates); keep the current heuristic scoring only as a logged last-resort fallback.
- **EPC export** (new capability): export a module configuration (or all modules) to EB-compatible `.epc` files — standard ECUC ARXML with the package/naming layout EB Tresos expects, deterministic ordering, including preserved unknown parameters.
- Validate import→generate against the MCAL_R440 reference project (`cmpBASe/` oracle) and import→export→re-import for lossless round-trip.

## Impact

- Affected specs: `eb-value-import` (new capability spec), `epc-export` (new capability spec)
- Affected code:
  - `autosar_configurator/core/config_manager.py` (`load_configuration`, `_cleanup_invalid_parameters`, `_normalize_definition_refs`)
  - `autosar_configurator/core/parser/arxml_parser.py` (multi-module parse)
  - `autosar_configurator/core/serializer/ecuc_serializer.py` (unknown-parameter passthrough; EPC export layout)
  - `autosar_configurator/core/workspace_manager.py` (`import_eb_project` multi-module matching; export entry point)
  - `autosar_configurator/ui/` (unknown-parameter warnings; export menu action)
- Out of scope: POST-BUILD `VARIATION-POINT` structural parsing (tracked as a follow-up change; largest effort, orthogonal to these fixes).

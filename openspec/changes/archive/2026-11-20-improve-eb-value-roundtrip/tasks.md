# Tasks

## 1. Unknown-parameter preservation (highest priority — data loss)

- [x] 1.1 Make `unknown_parameters` a first-class field on `EcucContainerValue` (configuration model)
- [x] 1.2 `_cleanup_invalid_parameters()`: populate the field (copy semantics — values stay in parameter_values so generator/serializer keep seeing them; see design.md), replace `print` with logger
- [x] 1.3 `ecuc_serializer.py`: unknown parameters written out via parameter_values (verified by round-trip test; explicit dual-write removed to avoid duplication)
- [x] 1.4 Parser/load: unrecognised values are flagged in `unknown_parameters` during load cleanup (round-trip stable)
- [x] 1.5 UI: warning badge (⚠️) + tooltip listing unknown parameter names on container instances (davinci_tree_view)
- [x] 1.6 Test: import EPC with foreign parameter → save → reload → value intact

## 2. Multi-module value files

- [x] 2.1 `ArxmlParser.parse_all_module_configurations()` returning all `ECUC-MODULE-CONFIGURATION-VALUES`
- [x] 2.2 `load_configuration()`: select the configuration matching the manager's module; warn on extras
- [x] 2.3 `import_eb_project()`: register bundled modules from multi-module files (EpcFileScanner.list_module_names)
- [x] 2.4 Test: two-module EPC file imports both

## 3. Exact DEFINITION-REF resolution

- [x] 3.1 `_normalize_definition_refs()`: exact structural match first (ref leaf / instance name / deterministic '_suffix' stripping / choice-container transparency), heuristic scoring only as fallback
- [x] 3.2 Log every heuristic remap (container, original ref, chosen def) as warning; exact remaps at debug
- [x] 3.3 Test: instance-named refs resolve without heuristic; sparse-container case falls back with logged warning

## 4. EPC export

- [x] 4.1 Analyzed reference EPC layout (package short-name = module name, AUTOSAR_00046.xsd schemaLocation)
- [x] 4.2 `EcucValueSerializer.export_epc()` (deterministic ordering, unknown parameters included via parameter_values)
- [x] 4.3 `WorkspaceManager.export_epc()` (one/all modules) + File menu action "Export EPC Files..." in main window/project controller
- [x] 4.4 Test: import→export→re-import semantic equality; double-export byte-identical; EB layout conventions

## 4b. Standalone value file import (counterpart of EPC export)

- [x] 4b.1 `File → Import Value File...`: replaces the selected module's configuration from an .epc/.arxml/.xdm file, with replace-confirmation, module-containment check (lists contained modules on mismatch), undo-stack reset, provenance recording, reference re-resolution, tree refresh, and unknown-parameter count in the summary

## 5. Regression against reference oracle

- [x] 5.1 Full 25-module generation against MCAL_R440 reference: 3018 diff lines == pre-change baseline exactly (zero regression; remaining diffs are pre-existing codegen gaps outside this change). Move-semantics regression in Os MPU output caught and fixed by switching to copy semantics.
- [x] 5.2 Full test suite: 416 passed, 2 skipped

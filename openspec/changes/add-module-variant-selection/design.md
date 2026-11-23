# Design: Close 1-of-N Module Implementation Variant Loop (Phase 1)

## Context

This codebase carries four distinct, orthogonal axes that frequently share the word "variant":

1. **Module implementation variant (this change)**: Distinct ECUC definitions and implementations for the same standard BSW module short name (e.g. `/MICROSAR/CanTrcv_GenericCan/CanTrcv` vs `/MICROSAR/CanTrcv_Tle9255/CanTrcv`), differentiated by hardware transceiver, vendor, or feature set.
2. **ECU configuration variant**: Parameter/container override layers for vehicle variants (`project.variants`, `configuration.variant_overrides`, `EcucContainerValue.variant`, `variant:*` XPath functions).
3. **ConfigClass**: Parameter binding time (`PRE-COMPILE`, `LINK-TIME`, `POST-BUILD`) orthogonal to module implementation variant.
4. **Chip / Derivative**: MCU derivative (`selected_chip`, `derivative_uuid`, `PackageFile.chips`, `DerivativeMapping_*.xml`).

Phase 1 closes the end-to-end **1-of-N single-variant** workflow: a project still holds at most one active `ConfigurationManager` per module `short_name`, while ensuring that selecting, importing, validating, generating, restoring, and switching that module's implementation variant is exact, transparent, and collision-free. **M-of-N multi-variant coexistence** in the same project requires decoupling `config_name` from `module_def.short_name` across project dictionaries, files, and `as:modconf()` and is explicitly deferred to Phase 2.

## Goals / Non-Goals

- **Goals**:
  - Eliminate silent cross-variant contamination during SIP partitioning, config loading/extraction, definition path comparison, deleted-module restoration, and v8 migration.
  - Provide a safe, previewable, atomic 1-of-N `switch_module_variant` capability.
  - Isolate project-level template and `INCLUDE` overlays by variant package directory (`templates/<pkg_dir_name>/`).
  - Surface variant definition identities clearly in the UI and prevent accidental simultaneous selection of sibling variants.
- **Non-Goals**:
  - Allowing two different implementation variants of the same module `short_name` to be active simultaneously in one project (Phase 2).
  - Wiring `VENDOR-API-INFIX` / `MODULE-DESCRIPTION-REF` C API prefix generation across BSW templates (Phase 2).
  - Changing `.dpa` schema (`format_version` stays 8) or breaking legacy Format ≤7 projects.

## Decisions

- **D1 — Inferring `module_name` in `definition_refs.same_definition()` and passing it at callsites**:
  - `module_relative(ref, module_name=None)` slices after `parts[2]` when `module_name` is `None`, which leaves the `<Module>` segment in 3-segment vendor paths (`/MICROSAR/CanTrcv_Tle9255/CanTrcv/...` -> `CanTrcv/CanTrcvGeneral`) while stripping it from `/AUTOSAR/EcucDefs/CanTrcv/CanTrcvGeneral` (`CanTrcvGeneral`).
  - Decision: When `same_definition(ref_a, ref_b, module_name=None)` is called without `module_name`, if either reference starts with `/AUTOSAR/EcucDefs/<Module>/` (or `/AUTOSAR/EcucDefs/<Module>`), infer `module_name = <Module>` before delegating to `module_relative()`. Also pass `module_name` explicitly at core/UI callsites (`configuration_model.py`, `config_manager.py`, `enable_conditions.py`, `davinci_tree_view.py`, etc.), and fix `structural_rules.py` `_get_container_def` to use `definition_refs.module_relative` rather than hardcoded `parts[3:]`.
  - Alternatives considered: Always stripping to the last N segments without knowing `module_name`. Rejected because container nesting depth varies and sub-package counts vary across vendors.

- **D2 — `SipScanner` `BSW-IMPLEMENTATION` attribution & non-broadcast partitioning**:
  - Decision: In `SipScanner._extract_module_and_role`, when a file contains `BSW-IMPLEMENTATION`, inspect `VENDOR-SPECIFIC-MODULE-DEF-REF` (extracting its leaf segment) before stripping `_Impl` from `SHORT-NAME`. In `partition_module_files`, also extract `BSW-IMPLEMENTATION` `VENDOR-SPECIFIC-MODULE-DEF-REF` / `PRECONFIGURED-CONFIGURATION-REF` / `RECOMMENDED-CONFIGURATION-REF` and package prefix to bind IMPL/MemMap/Pre/Rec fragments to the exact `ECUC-MODULE-DEF` partition. For any fragment that still cannot be attributed to a specific partition (excluding shared files explicitly referencing multiple or belonging to a single module), do not broadcast it into every variant partition — leave it unattached/warn rather than risking cross-variant merge corruption or false `SipMergeError`.
  - Alternatives considered: Keeping filename heuristics (`*_MemMap.arxml`). Rejected per project design rule that filenames are non-authoritative.

- **D3 — Strict variant matching on extract, load, restore, and upgrade**:
  - Decision:
    - `DaVinciProjectImporter._extract_module_config` and `ConfigurationManager.load_configuration`: when `expected_def_ref` / `module_def.ar_path` is known and exact-matching blocks exist, select only exact-matching blocks instead of merging sibling variant blocks that happen to share `def_leaf == module_name` or `short_name == module_name`.
    - `WorkspaceProject.restore_deleted_module` and `upgrade_to_v8`: extract `DEFINITION-REF` from the archived/existing configuration (or `mgr.module_def.ar_path` / `definition_ref`) and match via `find_package(libraries, def_ref)` first. Fall back to `short_name` only when `def_ref` is absent or `/AUTOSAR/EcucDefs/<Module>` AND there is a unique candidate package; if multiple variant packages share that module name and the target cannot be disambiguated, raise a clear `ValueError` instead of guessing alphabetically.

- **D4 — Controlled two-phase `switch_module_variant`**:
  - Decision: Implement `list_module_variant_packages(module_name)` and `switch_module_variant(module_name, target_pkg, target_lib_index, preview_only=False, confirm=None)` on `WorkspaceProject`.
  - Flow:
    1. Parse target `EcucModuleDef` (without mutating the project) and compute a `VariantSwitchPlan` comparing the current `EcucModuleConfiguration` against the target definition and target package baseline (`kept_paths`, `unknown_paths`, `missing_required_containers`, `baseline_merge_preview`).
    2. When `preview_only=True`, return `VariantSwitchPlan` immediately.
    3. Otherwise capture backup via `_capture_module_replace_backup(module_name)`, re-bind `module_def`, `module_defs`, `packages`, `module_entries` (`definition`, `library`, `package_record`), preserve existing configuration containers/values while running `repair_definition_refs()` + `_cleanup_invalid_parameters()` so incompatible parameters move cleanly to `unknown_parameters` without silent deletion, reconcile baseline (`reconcile_baseline`) if confirmed, refresh `load_ecu_resources()` and `resolve_all_references(force=True)`, and roll back completely via `_restore_module_replace_backup` if anything raises or fails confirmation.

- **D5 — Variant-scoped template overlay (`templates/<pkg_dir_name>/`)**:
  - Decision: Add `project_paths.package_dir_name(project, module)` returning `pkg.root.name` when a Format 8 `ModulePackage` exists. Pass `package_dir_name` into `CodeGenerator`, `GenerationController`, `DaVinciTreeView`, `ProjectPropertiesDialog`, and `ecu_resource_diagnostics`. When `package_dir_name` is set and `package_dir_name != module_name`, `CodeGenerator._discover_template_types` and `_build_include_search_paths` search `templates/<package_dir_name>/` first, then `templates/<module_name>/`, then the package template dir, then `user_template_dir`. Non-variant modules and Format ≤7 projects follow the exact existing lookup and keep identical fingerprints.

- **D6 — UI disambiguation, mutual exclusion, and switch action**:
  - Decision:
    - `IntegrationWizard`: Check `is_installed` by matching `cand.package.manifest.definition == entry.definition` (and report sibling variants of an installed module as `"Other Variant"` rather than `"Installed"`). Display a Variant / Definition column (or clear label) alongside `Module`, allow filtering by `definition` and `pkg.root.name`, enforce mutual exclusion when checking two variants of the same `module` (automatically unchecking or warning against the conflicting sibling), skip multi-variant modules without an installed match in `_select_all()` (showing a clear notice), block duplicate modules in `ConfirmationPage.validatePage()`, and show `SW Version` and `Vendor API Infix` in the detail panel.
    - `DaVinciTreeView` & `ProjectPropertiesDialog`: Show variant badge/suffix and full `ar_path` tooltip on module nodes; add `"切换模块变体 (Switch Variant)..."` in module context menu when `list_module_variant_packages(module_name)` returns alternative variants; display `Definition` path column/details for each module in `ProjectPropertiesDialog`.

## Risks / Trade-offs

- **Stricter error behavior on ambiguous archives**: `restore_deleted_module` will now raise `ValueError` instead of silently binding to the first alphabetical package if an archive lacks a specific `DEFINITION-REF` while multiple sibling variants exist in registered libraries. Mitigation: error message lists all candidate definitions and package paths clearly.
- **Newly surfaced validation errors**: Fixing `same_definition()` and `structural_rules.py` for 3-segment vendor paths will allow multiplicity and `ENABLE` checks that previously silently missed to fire. Mitigation: verify against existing test suite including `test_sip_multi_variant_module_selects_matching_definition_by_dpa`.
- **Fingerprint stability**: Non-variant modules and existing tests must keep identical generator fingerprints (`test_template_sources.py`, `verify_fingerprints.py`). Mitigation: keep `_calculate_fingerprint` backward-compatible for standard modules and verify all fingerprint tests after Step 3.

## Migration Plan

- No `.dpa` format bump (`format_version` remains `8`) and no on-disk schema migration needed.
- Existing `templates/<Module>/` overlays continue to work as fallback underneath `templates/<pkg_dir_name>/`.


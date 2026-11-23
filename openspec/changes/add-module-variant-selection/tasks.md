# Tasks: Close 1-of-N Module Implementation Variant Loop (Phase 1)

## 1. Core Fixes & Variant Switching (Step 2)
- [x] 1.1 Fix `definition_refs.same_definition()` to infer `module_name` from `/AUTOSAR/EcucDefs/<Module>/...` when omitted, and pass `module_name` explicitly at callers (`configuration_model.py`, `config_manager.py`, `enable_conditions.py`).
- [x] 1.2 Fix `structural_rules.py` `_get_container_def` to resolve relative paths via `definition_refs.module_relative()` instead of hardcoded `parts[3:]`.
- [x] 1.3 Fix `SipScanner._extract_module_and_role` to prioritize `BSW-IMPLEMENTATION/VENDOR-SPECIFIC-MODULE-DEF-REF` over `SHORT-NAME` suffix stripping, and update `SipScanner.partition_module_files` so unmatched variant fragments are not broadcast to every partition.
- [x] 1.4 Restrict `DaVinciProjectImporter._extract_module_config` and `ConfigurationManager.load_configuration` to select only exact `DEFINITION-REF` matches when present instead of merging sibling variants.
- [x] 1.5 Update `WorkspaceProject.restore_deleted_module` and `upgrade_to_v8` to match packages by archived/configured `DEFINITION-REF` first and raise an explicit error on multi-variant ambiguity.
- [x] 1.6 Implement `WorkspaceProject.list_module_variant_packages()` and `WorkspaceProject.switch_module_variant()` with `VariantSwitchPlan` preview, baseline reconciliation, atomic rollback, and reference re-resolution.

## 2. Generator Variant Overlay (Step 3)
- [x] 2.1 Add `project_paths.package_dir_name(project, module)` while keeping `template_sources()` return signature backward-compatible.
- [x] 2.2 Add optional `package_dir_name` to `CodeGenerator` and search `templates/<package_dir_name>/` before `templates/<module_name>/` and package templates (both template discovery and `INCLUDE` search paths).
- [x] 2.3 Wire `package_dir_name` through `GenerationController` and `ecu_resource_diagnostics.py`, preserving generator fingerprint stability for existing non-variant modules.

## 3. UI Disambiguation & Switch Flow (Step 4)
- [x] 3.1 Update `IntegrationWizard` (`ModuleSelectionPage` & `ConfirmationPage`) to display variant/definition paths, compute `is_installed` by exact `definition`, show `SW Version`/`Vendor API Infix`, search by `definition` and package dir name, enforce per-module variant mutual exclusion, and skip ambiguous multi-variant modules in `Select All Compatible`.
- [x] 3.2 Update `DaVinciTreeView` to display variant identity/tooltip on module nodes, pass `package_dir_name` for template inspection, pass `module_name` to `same_definition()`, and add `"切换模块变体 (Switch Variant)..."` context menu action when alternatives exist.
- [x] 3.3 Update `ProjectPropertiesDialog` to display each configured module's active `definition` path and pass `package_dir_name` on the Templates tab.
- [x] 3.4 Connect `switch_module_variant_requested` in `DaVinciMainWindow` and `ProjectController` with variant picker + switch impact preview dialog and post-switch UI/reference refresh.

## 4. Tests & Verification (Step 5)
- [x] 4.1 Add unit tests in `tests/core/test_definition_refs.py` for 3-segment vendor path matching and multiplicity validation.
- [x] 4.2 Add integration tests in `tests/core/test_davinci_project_import_e2e.py` (or focused core test) for infixed `MemMap` attribution, exact restore/upgrade, single-file multi-variant extraction, and `switch_module_variant` preview + rollback.
- [x] 4.3 Add generator tests in `tests/generator/test_template_sources.py` for `templates/<pkg_dir_name>/` precedence over `templates/<Module>/` and fingerprint stability.
- [x] 4.4 Add UI tests in `tests/ui/test_integration_wizard.py` for variant disambiguation, exact `is_installed` status, mutual exclusion, and tree/switch flow; run full relevant pytest suites (`QT_QPA_PLATFORM=offscreen`) and `openspec validate --all --strict`.


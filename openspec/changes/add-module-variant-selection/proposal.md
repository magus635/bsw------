# Close 1-of-N Module Implementation Variant Loop (Phase 1)

## Why

While SIP module partitioning and Format 8 `ModuleEntry.definition` currently allow importing a single BSW module implementation variant (for example, `/MICROSAR/CanTrcv_Tle9255/CanTrcv` instead of `/MICROSAR/CanTrcv_GenericCan/CanTrcv`), 1-of-N module implementation variant handling still breaks across five areas:

1. **Multi-segment vendor path matching**: Vendor paths such as `/Pkg/Variant/Module/...` (e.g. `/MICROSAR/CanTrcv_Tle9255/CanTrcv/CanTrcvGeneral`) fail `definition_refs.same_definition()` when `module_name` is omitted and fail `structural_rules.py` fallback path slicing (`parts[3:]`).
2. **SIP scanning and config extraction leaks**: `SipScanner` misgroups infixed `BSW-IMPLEMENTATION` files (such as `CanTrcv_30_Tle9255_MemMap.arxml`) into separate orphan modules and broadcasts unmatched files across all variant partitions; `_extract_module_config` and `ConfigurationManager.load_configuration` can merge configuration blocks from different variants when they appear in the same file.
3. **Blind restore/upgrade and missing variant switch**: `WorkspaceProject.restore_deleted_module` and `upgrade_to_v8` match only by `short_name` and silently bind the wrong sibling variant (e.g. restoring `CanTrcv_Tle9255` onto `CanTrcv_GenericCan`); there is no controlled workflow to switch a configured module from one variant package to another.
4. **Unisolated template overlays**: Project template overlays (`templates/<Module>/`) cannot isolate template or `INCLUDE` overrides per variant package directory (`pkg.root.name`).
5. **Blind UI**: `IntegrationWizard`, `DaVinciTreeView`, and `ProjectPropertiesDialog` hide variant identities, mislabel sibling variants as `Installed`, allow selecting multiple variants of the same module simultaneously (silently clobbering the first), and lack a variant-switching entry point.

## What Changes

- **Core path matching & validation**: Infer `<Module>` from `/AUTOSAR/EcucDefs/<Module>/...` in `definition_refs.same_definition()` when `module_name` is omitted, pass `module_name` explicitly across core/UI callsites, and fix `structural_rules.py` multi-segment path fallback slicing.
- **Core SIP attribution & strict variant config matching**: Resolve `BSW-IMPLEMENTATION` module ownership via `VENDOR-SPECIFIC-MODULE-DEF-REF` before falling back to `SHORT-NAME` suffix stripping; stop broadcasting unmatched variant fragments across partitions; match `expected_def_ref` / `module_def.ar_path` strictly before falling back to short name in config extraction/loading; resolve `DEFINITION-REF` accurately in `restore_deleted_module` and `upgrade_to_v8` (raising an error on ambiguity instead of silently guessing).
- **Controlled variant switching**: Add `WorkspaceProject.list_module_variant_packages()` and `WorkspaceProject.switch_module_variant()` with pre-switch compatibility preview (`VariantSwitchPlan`), baseline merge integration, atomic backup/rollback, and cross-module reference re-resolution.
- **Generator variant-scoped overlays**: Resolve `templates/<pkg_dir_name>/` before `templates/<Module>/` and before package templates when `pkg_dir_name != module_name` (for both templates and `INCLUDE` macro search paths), keeping legacy and non-variant behavior identical.
- **Variant-aware UI**: Display variant/definition paths and exact installation status in `IntegrationWizard`, enforce per-module variant mutual exclusion, skip ambiguous multi-variant modules in "Select All Compatible", display active definition paths in `DaVinciTreeView` and `ProjectPropertiesDialog`, and add a "Switch Variant..." context menu action wired through `ProjectController`.
- **Non-Goal (deferred to Phase 2)**: M-of-N simultaneous coexistence of multiple implementation variants of the same standard BSW module short name within a single project (e.g. `CanTrcv_Tja1043` and `CanTrcv_Tle9255` active concurrently).

## Impact

- **Affected specs**:
  - `module-packages` (ADDED)
  - `config-definition-refs` (ADDED)
  - `code-generation` (MODIFIED)
- **Affected code**:
  - `autosar_configurator/core/model/definition_refs.py`
  - `autosar_configurator/core/rules/structural_rules.py`
  - `autosar_configurator/generator/eb/enable_conditions.py`
  - `autosar_configurator/core/model/configuration_model.py`
  - `autosar_configurator/core/davinci_importer.py`
  - `autosar_configurator/core/config_manager.py`
  - `autosar_configurator/core/workspace_manager.py`
  - `autosar_configurator/core/project_paths.py`
  - `autosar_configurator/generator/generator.py`
  - `autosar_configurator/ui/controllers/generation_controller.py`
  - `autosar_configurator/core/hardware/ecu_resource_diagnostics.py`
  - `autosar_configurator/ui/wizards/integration_wizard.py`
  - `autosar_configurator/ui/widgets/davinci_tree_view.py`
  - `autosar_configurator/ui/dialogs/project_properties_dialog.py`
  - `autosar_configurator/ui/controllers/project_controller.py`
  - `autosar_configurator/ui/davinci_main_window.py`


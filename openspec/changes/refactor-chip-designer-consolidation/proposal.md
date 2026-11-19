# Change: Consolidate Chip Definition Designer & Single-Source ECU Sync

## Why

The Chip Definition Designer (`ChipDefinitionDesignerDialog`) and `ChipRepairWizard` currently overlap heavily, and a chip's hardware facts (CPU cores, peripherals, pinout) are duplicated across four separate sections (`ecu_resources`, `metadata.cores`, `resources`, `ports`) that users must manually sync across three different tabs. Additionally, manual test artifact `SC300_COPY.yaml` remains in the built-in chip library.

## What Changes

- **Unified Single-Source Sync (`sync_derived_fields_from_ecu`)**: Add a single core helper that derives/synchronizes `metadata.cores`, `resources` (peripherals), and `ports` (pinout) from `ecu_resources` in one deterministic operation, eliminating drift across the four representations.
- **Consolidated Designer Actions**: Add a one-click **"从 ECU 同步全部派生数据"** action and a **"批量确认待确认项…"** dialog directly in `ChipDefinitionDesignerDialog` so routine maintenance no longer requires jumping between tabs or launching the separate `ChipRepairWizard` (which remains available for backwards compatibility with existing `chip-repair` requirements).
- **Chip Library Cleanup**: Remove the stray test copy `autosar_configurator/data/chips/SC300_COPY.yaml` (and its history file if present).

## Impact

- Affected specs: `chip-library`
- Affected code:
  - `autosar_configurator/core/hardware/ecu_resources.py` (or `chip_database.py`)
  - `autosar_configurator/ui/dialogs/chip_definition_designer_dialog.py`
  - `autosar_configurator/data/chips/SC300_COPY.yaml`
- Existing `chip-repair` requirements and all 5 `ChipRepairWizard` entry points remain intact and backwards-compatible.

## 1. Core Single-Source Sync Helper
- [x] 1.1 Implement `sync_derived_fields_from_ecu(chip: ChipDefinition) -> Dict[str, Any]` to synchronize `metadata["cores"]`, `resources` (peripherals), and `ports` (pinout) from `chip.ecu_resources` in one pass, returning a summary of updated sections.
- [x] 1.2 Add unit tests verifying `sync_derived_fields_from_ecu` updates cores, peripherals, and ports from `ecu_resources` while leaving sections untouched when `ecu_resources` lacks corresponding keys.

## 2. Designer Consolidation
- [x] 2.1 Add a unified **"🔄 从 ECU 同步全部"** toolbar action in `ChipDefinitionDesignerDialog` calling `sync_derived_fields_from_ecu` (with confirmation when overwriting existing manual peripherals/pins) and refreshing Basic, Peripherals, Pinout, and Preview views.
- [x] 2.2 Add a **"✓ 批量确认待确认项…"** dialog in `ChipDefinitionDesignerDialog` listing all non-placeholder `metadata.unconfirmed` entries with checkboxes so users can confirm multiple items without opening `ChipRepairWizard`.
- [x] 2.3 Add UI tests in `tests/ui/test_chip_designer_edits.py` covering one-click ECU sync and batch confirmation of `unconfirmed` marks.

## 3. Chip Library Cleanup & Verification
- [x] 3.1 Remove stray test artifact `autosar_configurator/data/chips/SC300_COPY.yaml` (and any matching `history/SC300_COPY.yaml`).
- [x] 3.2 Run full chip UI + core test suites (`tests/ui/test_chip_*.py`, `tests/core/test_chip_designer.py`, `tests/core/test_chip_repair.py`) and confirm zero regressions.

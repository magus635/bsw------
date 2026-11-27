# Design: Communication Workbench & Multi-Module DBC Derivation

## Context

AUTOSAR Classic communication spans lower drivers (`Can`, `CanTrcv`), interface and state managers (`CanIf`, `CanSM`, `ComM`), transport (`CanTp`), global PDU pool (`EcuC`), router (`PduR`), and COM signals (`Com`). Existing workbenches (`RteSchmWorkbench`, `MemoryMapWorkbench`) establish clean separation between pure-Python domain services and PySide6 dialogs.

## Goals / Non-Goals

- **Goals**:
  - Provide end-to-end visibility and safe editing across `ComM`, `CanSM`, `CanIf`, `Can`, `CanTrcv`, `CanTp`, `PduR`, `Com`, and `EcuC`.
  - Handle both Vector DaVinci (`/ActiveEcuC/<Mod>/...` + split `PduR` dual `EcuC/Pdu` refs) and EB Tresos (`/<Mod>/<Mod>/...` + single `EcuC/Pdu`) styles seamlessly.
  - Provide deterministic, previewable multi-module DBC derivation that recognizes existing PDUs instead of duplicating them and respects Pre-compile locks (`PreLockedError`).
  - Provide atomic multi-module Cancel rollback and single `QUndoCommand` (`ReplaceMultipleModulesCommand`) undo/redo integration.
- **Non-Goals**:
  - Real-time Ethernet/SOME/IP/LIN/FlexRay channel editing or SWC Port-to-Com Data Mapping (deferred to P2).
  - BSW C code generation templates for `Com`/`PduR`/`CanIf` (covered separately by template packs).

## Decisions

1. **Snapshot-based multi-module transaction**: Reuse `snapshot_rte_config` / `restore_rte_config` across all loaded communication modules (`COMM_MODULES`) inside `CommunicationWorkbenchService.capture_snapshots()` / `restore_snapshots()`. Cancel immediately restores pre-open state; OK pushes `ReplaceMultipleModulesCommand` when `has_edits` is True.
2. **Multi-reference handling for `ComIPduSignalRef`**: `ComIPdu` stores single signal references in `reference_values["ComIPduSignalRef"]` when count == 1 and multi-references in `multi_reference_values["ComIPduSignalRef"]` when count > 1. `CommunicationWorkbenchService` and `dbc_sync` always inspect both maps and convert cleanly when appending a second signal.
3. **Single-emission anchor for `CommunicationValidationRule`**: Because `ValidationEngine` executes per module, `CommunicationValidationRule` executes only on the first loaded module in `ANCHOR_PRIORITY = ("Com", "PduR", "CanIf", "CanSM", "ComM", "Can")` so cross-module diagnostics appear once per project validation run and contain `workbench_tab=<idx>; code=<code>` for direct jump from `ProblemsView`.
4. **Motorola MSB bit stepping**: `ComBitPosition` on `BIG_ENDIAN` signals follows AUTOSAR/Vector Motorola forward byte numbering (`bit_in_byte` counts down `7..0`, wrapping to `byte_idx + 1, bit 7`).
5. **Pre-empty/stub safety**: Empty/stub communication modules without configured frames emit zero false-positive errors so synthetic test projects and newly initialized projects validate cleanly.

## Risks / Trade-offs

- **Re-syncing OEM DBCs with hashed PDU names**: DaVinci hashes suffix names (`MCU_Temp_0x227_oMotorDomain_6bf380d4_Tx`). `plan_dbc_sync` matches existing messages primarily by `(direction, can_id, is_extended)` and secondarily by sanitized short-name prefix so existing hashed ECUC PDUs are matched and updated cleanly in place.
- **Left Navigation Rail height budget**: Adding a 4th workbench button brings `LeftNavigationBar` to 11 buttons; slightly compacting `NavRailButton` height from `54px` to `50px` keeps all items visible on laptop displays.

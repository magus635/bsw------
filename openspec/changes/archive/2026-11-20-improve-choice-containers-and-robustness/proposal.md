## Why

When loading projects containing vendor-specific containers (such as Choice Containers or containers where references are serialized as textual parameters like `RegionSelect`), the configuration manager emits multiple false-positive warnings and stores reference values under `unknown_parameters`. Furthermore, startup scripts and environment diagnostics need hardened handling for invalid or foreign-architecture virtual environments to ensure frictionless launches across developer machines.

## What Changes

- Enhance `ConfigManager._cleanup_unknown_parameters` to recognize vendor-pattern reference-as-parameter storage (e.g. `RegionSelect` pointing to `MemoryBlockRef`), mapping them correctly or classifying them cleanly without spamming warnings.
- Update `start.sh` with architecture verification to detect unexecutable/corrupted Python binaries in virtual environments and gracefully fall back to functional system Python installations.
- Ensure unknown and vendor-specific parameters are accurately preserved without data loss and represented cleanly in UI inspection points.

## Impact

- Affected specs: `core-configuration`
- Affected code: `autosar_configurator/core/config_manager.py`, `start.sh`

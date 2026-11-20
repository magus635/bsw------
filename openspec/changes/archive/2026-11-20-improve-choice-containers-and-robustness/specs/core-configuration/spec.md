## ADDED Requirements

### Requirement: Choice and Vendor Reference Normalization
The `ConfigManager` SHALL identify vendor-specific textual parameters that correspond to container references or choice selections (e.g., `RegionSelect` mapping to `MemoryBlockRef`), preserving the configuration values while eliminating false-positive unknown parameter warnings.

#### Scenario: Vendor textual reference mapped to container reference
- **WHEN** a container instance contains a textual parameter whose name matches the container short-name or a defined reference in the container definition
- **THEN** `ConfigManager` recognizes the value as a legitimate vendor configuration entry without logging unnecessary warnings
- **AND** the value remains intact in configuration values and accessible for code generation

### Requirement: Environment Architecture Verification
The launch automation scripts SHALL verify that virtual environment Python executables are compatible with the host architecture before attempting activation.

#### Scenario: Incompatible virtual environment binary
- **WHEN** a local `venv` or `.venv` directory contains an unexecutable or foreign architecture binary (e.g. x86_64 on Apple Silicon)
- **THEN** the script skips the invalid virtual environment with an informative message
- **AND** falls back to a functioning system Python executable

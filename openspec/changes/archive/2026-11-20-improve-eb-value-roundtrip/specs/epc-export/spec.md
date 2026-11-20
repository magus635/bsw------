# epc-export — Delta

## ADDED Requirements

### Requirement: EPC Export

The tool SHALL export a module configuration to an EB Tresos-compatible `.epc` file (ECUC ARXML with the package and naming layout produced by EB Tresos), for a single module or for all modules in the project. Export SHALL use deterministic ordering (sorted, consistent with the generator's conventions) and SHALL include preserved unknown parameters.

#### Scenario: Single-module export

- **WHEN** the user exports the Os module configuration to `.epc`
- **THEN** an `Os.epc` file is written whose module configuration EB Tresos can import without structural errors

#### Scenario: Lossless round-trip

- **WHEN** an EPC file is imported and immediately exported without edits
- **THEN** re-importing the exported file yields a configuration semantically identical to the first import (same containers, parameter values, and references)

#### Scenario: Deterministic output

- **WHEN** the same configuration is exported twice
- **THEN** the two files are byte-identical

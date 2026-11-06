## ADDED Requirements

### Requirement: Explicit Versioned vBRS Template Pack
The system SHALL load a versioned vBRS template pack only from an explicitly selected project or user template directory, without a built-in fallback or silently mixing MSR and DvC6 rules.

#### Scenario: No pack selected
- **WHEN** vBRS has no selected external template pack
- **THEN** generation reports the module as skipped and does not manufacture fallback code

### Requirement: Per-output Templates
The vBRS pack SHALL provide separate templates for vBrsCfg.h, vBrs_Lcfg.c, vBrs_Lcfg.h, Makefile.config.generated, EcuM.c, EcuM.h, EcuM_Cbk.h, EcuM_Error.h, EcuM_Generated_Types.h and parameterized SchM module headers. Static BrsMain implementation files SHALL NOT be classified as generated configuration outputs.

#### Scenario: Stub generation disabled
- **WHEN** valid vBRS input disables EcuM and SchM stubs
- **THEN** the four regular outputs are selected and no stub outputs are selected

#### Scenario: Conditional stubs enabled
- **WHEN** the selected generator version's confirmed stub conditions are satisfied
- **THEN** only the corresponding EcuM files and eligible SchM headers are selected using their exact declared filenames

### Requirement: Validated Rule Context
The system SHALL derive template context from actual configuration values and resolved module references using traceable rules. It SHALL preserve missing-versus-false and multiline-string semantics and SHALL reject unsupported active branches before emitting successful outputs.

#### Scenario: PLL disabled
- **WHEN** the confirmed PLL handling value is false
- **THEN** vBrsCfg.h omits the active BRS_ENABLE_PLLCLOCKS definition rather than defining it as zero

#### Scenario: Missing core reference
- **WHEN** active multicore output requires a core or stack reference that cannot be resolved
- **THEN** generation reports the offending input and produces no new successful output set

### Requirement: Safe Output Ownership and Dependency Tracking
The system SHALL validate destinations against explicit output roots, detect collisions with other generators and track templates, rules and cross-module dependencies in generation fingerprints.

#### Scenario: Existing EcuM output from another generator
- **WHEN** an intended stub destination conflicts with a file not owned by this template pack
- **THEN** generation reports the conflict without overwriting the existing file

#### Scenario: Referenced Os configuration changes
- **WHEN** a referenced Os core mapping changes while vBRS values remain unchanged
- **THEN** cached generation is invalidated and the new mapping is reflected in both linked C and header outputs

### Requirement: Evidence-based Verification
Each output family SHALL have rule and rendering tests. Baseline comparisons SHALL explicitly identify their source and allowed normalization; unavailable reference outputs SHALL be reported as unverified rather than equivalent.

#### Scenario: RTE SchM sample encountered
- **WHEN** a candidate SchM baseline identifies the RTE generator instead of the vBRS stub generator
- **THEN** it is excluded from vBRS stub equivalence comparisons

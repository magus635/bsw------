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

### Requirement: Complete Configurable Behavior Coverage
The implementation SHALL cover the supplied MSR 14.09.01 and DvC6 14.09.02 JARs in separate profiles. Coverage SHALL include all 257 vBRS definition leaves, 22 container definitions, external metadata and configuration inputs, dynamic reads, setup and validation actions, output selection and reachable rendering branches. A definition-field reference alone SHALL NOT count as a recovered or tested rule.

#### Scenario: Assembly preset changes driver configuration
- **WHEN** a selected veHaaS assembly implies changes to actual vBRS or vBaseEnv values
- **THEN** the pack provides traceable setup proposals or conflict diagnostics, requires explicit application before changing source values, and routes resolved values through the ordinary output rules

#### Scenario: Branch remains unsupported
- **WHEN** an applicable JAR branch has not been implemented or its input mapping remains unresolved
- **THEN** affected generation is rejected and the overall implementation remains incomplete, even when current sample files pass comparison

#### Scenario: Informational parameter
- **WHEN** an audited parameter has no effect on output, such as a documentation-only field
- **THEN** it remains represented in the inventory and input model with evidence and a no-output test rather than an invented C macro

### Requirement: Exact Baseline Replay and Honest Equivalence
For matching inputs the pack SHALL reproduce the four existing vBRS reference files byte-for-byte in a test-only mode with explicitly frozen metadata, encoding and line endings. Normal generation SHALL use truthful generator identity and report every explicitly allowed identity or timestamp difference without broad normalization. Full equivalence acceptance SHALL require applicable original vBRS reference outputs for conditional output families and each version profile.

#### Scenario: Current sample replay
- **WHEN** the matching complete input snapshot and test metadata are supplied
- **THEN** all four generated files compare byte-for-byte with their frozen original references and any unexpected difference fails acceptance

#### Scenario: No original Stub reference
- **WHEN** only synthetic fixtures, bytecode evidence, or same-named RTE/EcuM outputs are available
- **THEN** rule tests may pass but original vBRS Stub equivalence remains unverified and full equivalence acceptance remains incomplete

#### Scenario: Source configuration is stale
- **WHEN** the existing output and current input snapshot disagree
- **THEN** the mismatch is reported and matching inputs are obtained instead of hardcoding old output values into templates

## ADDED Requirements

### Requirement: Enable Conditions Read From Definitions
The definition parser SHALL read `<a:da name="ENABLE" type="XPath">` on `v:ctr`, `v:lst`, `v:chc`, `v:var` and `v:ref` elements of an EB tresos module definition, keeping the expression from `expr`, or from the first `a:tst/@expr` when `expr` is absent. A condition on a `v:lst` SHALL apply to the whole list; a condition on any other element SHALL apply to that element.

#### Scenario: List-level condition
- **WHEN** the definition has `<v:lst name="OsTaskTimingProtection">` with an `ENABLE` XPath expression
- **THEN** the `OsTaskTimingProtection` container definition keeps that expression as its list condition

#### Scenario: Parameter and reference conditions
- **WHEN** `v:ref name="OsResourceCoreRef"` has `ENABLE` with expression `(../OsResourceProperty != 'LINKED') or (../OsResourceLinkedToResScheduler = 'true')`
- **THEN** the `OsResourceCoreRef` reference definition keeps that expression

#### Scenario: No condition
- **WHEN** an element has no `ENABLE` attribute
- **THEN** its definition has no condition and the element is always enabled

### Requirement: Enable Result Mapping
The `true` and `false` attributes of an `ENABLE` condition SHALL map the expression's result to the enable state, and a fixed `ENABLE` value without an expression SHALL NOT be a condition, being the initial state of a new optional item whose actual state the value file records.

#### Scenario: Inverted result mapping
- **WHEN** `v:var name="OsAppErrorHook"` has `ENABLE` with `true="false" false="true"` and its expression is true for the configuration
- **THEN** `OsAppErrorHook` is disabled

#### Scenario: Fixed value is not a condition
- **WHEN** the definition of `EcucHardware` has `<a:da name="ENABLE" value="false"/>` and the value file configures `EcucHardware` without disabling it
- **THEN** `EcucHardware` is enabled

### Requirement: Disabled Items Are Not Visible To Templates
Before any template is rendered, and after every module of the project is loaded, the generator SHALL evaluate each condition top-down in document order and remove a node whose condition is false together with its subtree, so that templates cannot select, count, loop over or read it; conditions inside a removed subtree SHALL NOT be evaluated.

#### Scenario: Timing protection under SC1
- **WHEN** `OsOS/OsScalabilityClass` is `SC1` and task `Task0` has an `OsTaskTimingProtection_0` instance
- **THEN** `node:exists(OsTaskTimingProtection/*)` is false in the context of `Task0`, and `Os_timingprotection_Cfg.h` defines `TOTAL_TPUSED_NUM` as `(0UL)`

#### Scenario: Timing protection under SC2
- **WHEN** `OsOS/OsScalabilityClass` is `SC2` with the same task configuration
- **THEN** `OsTaskTimingProtection_0` is visible to templates

#### Scenario: Mutually exclusive references
- **WHEN** a resource has `OsResourceProperty = 'LINKED'` and `OsResourceLinkedToResScheduler = 'false'`
- **THEN** `OsResourceLinkedResourceRef` is visible and `OsResourceCoreRef` is not

#### Scenario: Condition across modules
- **WHEN** a condition reads an EcuC value through `node:ref`
- **THEN** it is evaluated against the loaded EcuC configuration

#### Scenario: Module without conditions
- **WHEN** a module definition has no `ENABLE` attributes
- **THEN** the generated files are identical to those generated without condition evaluation

### Requirement: Condition Context
A condition SHALL be evaluated with the conditioned node of the configuration tree as XPath context, where the parent of a single (non-list) sub-container instance is the container that holds it, as in EB.

#### Scenario: Parameter in a single sub-container
- **WHEN** `OsAppErrorHook` in the single container `OsApplicationHooks` has a condition reading `../../OsApplicationCoreRef`
- **THEN** `../..` is the `OsApplication` instance that holds `OsApplicationHooks`

### Requirement: Unevaluable Conditions Keep Items Enabled
When a condition cannot be evaluated, because the expression is invalid or uses an unsupported function, the generator SHALL treat the item as enabled and SHALL report a warning in the generation result naming the node path and the expression, once per expression.

#### Scenario: Unsupported function
- **WHEN** a condition calls a function the XPath engine does not implement
- **THEN** the item stays visible to templates and the generation result contains a warning with the node path and the expression

### Requirement: Disabled Items Omitted From EPC Export
EPC export SHALL omit containers, parameters and references whose condition is false, evaluated as for generation, while the project's saved configuration SHALL keep their values.

#### Scenario: Export under SC1
- **WHEN** the Os module with `OsScalabilityClass = 'SC1'` and a configured `OsTaskTimingProtection_0` is exported to EPC
- **THEN** the EPC contains no `OsTaskTimingProtection` container, and the project's `ConfigValue/Os_Config.arxml` still contains it

#### Scenario: Condition becomes true again
- **WHEN** `OsScalabilityClass` is changed to `SC2` and the module is exported again
- **THEN** the EPC contains `OsTaskTimingProtection_0` with its saved values

### Requirement: Regeneration After Upgrade
The generator fingerprint SHALL include a version that changes with this behaviour, so that the first generation after the upgrade regenerates every module instead of keeping output produced without condition evaluation.

#### Scenario: Cached module after upgrade
- **WHEN** a module was generated before the upgrade and its configuration and templates are unchanged
- **THEN** the first generation after the upgrade regenerates it

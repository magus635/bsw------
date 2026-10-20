## ADDED Requirements

### Requirement: EB Number Types
The template engine SHALL evaluate XPath numbers (numeric literals, arithmetic, `count`, `string-length`, `number`, `sum`, `floor`, `ceiling`, `round`, `num:max`, `num:min`) as floating-point values, and the results of `num:i`, the `num:*toint` conversions and the `bit:*` functions as integer values, as EB tresos does.

#### Scenario: Arithmetic output
- **WHEN** a template contains `[!"1+1"!]`
- **THEN** the output is `2.0`

#### Scenario: Integer function output
- **WHEN** a template contains `[!"num:i(1+1)"!]`
- **THEN** the output is `2`

#### Scenario: Large number output
- **WHEN** a template contains `[!"100000000"!]`
- **THEN** the output is `1.0E8`

### Requirement: EB String Conversion
Expression output and variable assignment SHALL convert a floating-point value with Java `Double.toString` rules, an integer value without a fractional part, and a boolean as `true` or `false`; XPath string conversion inside expressions (`string()`, `concat()`) SHALL follow XPath 1.0, writing an integral number without a fractional part.

#### Scenario: Boolean output
- **WHEN** a template contains `[!"1 < 2"!]`
- **THEN** the output is `true`

#### Scenario: Number inside concat
- **WHEN** a template contains `[!"concat('a', 1+1)"!]`
- **THEN** the output is `a2`

### Requirement: Variables Hold Strings
`[!VAR!]` SHALL store a numeric, boolean or string result as its EB string form, and `[!FOR!]` SHALL store the loop variable as an integer string; a result that is a configuration node or node set SHALL be stored as before.

#### Scenario: Numeric literal variable
- **WHEN** a template contains `[!VAR "a" = "5"!][!"$a"!]`
- **THEN** the output is `5.0`

#### Scenario: Loop variable
- **WHEN** a template contains `[!FOR "i" = "0" TO "1"!][!"$i"!],[!ENDFOR!]`
- **THEN** the output is `0,1,`

### Requirement: XPath 1.0 Comparison
`=` and `!=` SHALL compare as booleans when either operand is a boolean, otherwise as numbers when either operand is a number, otherwise as strings; `<`, `>`, `<=` and `>=` SHALL compare as numbers.

#### Scenario: Two variables compare as strings
- **WHEN** variable `CeilingPriority` is set by `[!VAR "CeilingPriority" = "0"!]` and `[!IF "$CeilingPriority = $i"!]` is evaluated inside `[!FOR "i" = "0" TO "0"!]`
- **THEN** the condition is false

#### Scenario: Variable and number literal compare as numbers
- **WHEN** variable `a` is set by `[!VAR "a" = "0"!]` and `[!IF "$a = 0"!]` is evaluated
- **THEN** the condition is true

#### Scenario: Quoted string literals
- **WHEN** a template contains `[!"'0.0' = '0'"!]`
- **THEN** the output is `false`

#### Scenario: Task queue size with a resource linked to RES_SCHEDULER
- **WHEN** the intTest Os configuration is generated with the `Os_THA6_ASR21` templates, where `OsResource_0` is LINKED to RES_SCHEDULER on core 0 and no task or ISR references it
- **THEN** `Os_task_Cfg.h` defines `PRIORITY0_CORE0_QUEUESIZE` as `(2U)`, as EB tresos does

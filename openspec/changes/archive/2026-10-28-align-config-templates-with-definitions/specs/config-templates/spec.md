## ADDED Requirements

### Requirement: Templates Agree With The Module Definition
Every configuration template SHALL name only a container that exists in its module's definition, only parameters that exist in that container, and, for an enumeration whose literals the definition lists, only values among those literals.

#### Scenario: Template compared with the definition
- **WHEN** any template, bundled as a file or built in, is compared with the vendor definition of its module
- **THEN** its container exists, every adjustable and fixed parameter exists in that container, and every enumeration value is one of the listed literals

#### Scenario: Pull mode of the GPIO input template
- **WHEN** the template `GPIO Input Pin` is loaded
- **THEN** it offers `PortPinPullMode` with the values `PORT_INPUTMODE_NONE`, `PORT_INPUTMODE_PULLUP` and `PORT_INPUTMODE_PULLDOWN`

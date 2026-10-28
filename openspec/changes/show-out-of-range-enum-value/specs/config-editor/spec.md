## ADDED Requirements

### Requirement: Out-Of-Range Enumeration Value Shown As Stored
The enumeration editor of the configuration panel SHALL show a parameter's stored value even when it is not among the offered options, SHALL mark it as outside the allowed range, and SHALL NOT change the stored value by displaying it.

#### Scenario: Stored value not among the options
- **WHEN** a parameter whose options are `PORT_PIN_MODE_ALL` stores `PORT_PIN_MODE_GPIO` and its editor is shown
- **THEN** the editor shows `PORT_PIN_MODE_GPIO` marked as outside the allowed range, not "(未配置)", and its tooltip lists the allowed options

#### Scenario: Marked entry writes back the stored value
- **WHEN** the marked entry is selected
- **THEN** the value read from the editor is `PORT_PIN_MODE_GPIO`, without the marker text

#### Scenario: Stored value among the options
- **WHEN** the stored value is one of the options, or no value is stored
- **THEN** the editor offers exactly the options it offered before and adds no marked entry

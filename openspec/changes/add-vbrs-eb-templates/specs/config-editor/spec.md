## ADDED Requirements

### Requirement: Multiline String Parameters
The system SHALL read ECUC-MULTILINE-STRING parameter definitions and values, keep the text's line breaks, write them back unchanged on save, and let the user edit them as multiline text in the configuration panel.

#### Scenario: vBRS makefile user code
- **WHEN** a vBRS configuration with a two-line `vBRSMakefileUserCode` value is loaded and saved
- **THEN** the saved value has the same two lines

#### Scenario: Edited in the panel
- **WHEN** the user selects a multiline string parameter
- **THEN** the panel shows a multiline text editor with the value's lines

## ADDED Requirements

### Requirement: One Memory Map Window With Shared Settings And One Scan
The system SHALL provide one window for the memory map with a diagnostics tab and a layout tab. The window SHALL hold the settings (source directories, MemMap header directories, linker file), SHALL run one scan, and SHALL show the same scan result in both tabs. Changing the settings SHALL NOT start a scan; the window SHALL tell the user that the shown result may be out of date until the user starts a new scan. The scan SHALL NOT change the project configuration or any file it reads.

#### Scenario: One scan feeds both tabs
- **WHEN** the user starts a scan
- **THEN** one scan runs, and the diagnostics tab and the layout tab both show its result

#### Scenario: Cancelled scan
- **WHEN** the user cancels a running scan
- **THEN** the scan stops and neither tab shows a partial result

#### Scenario: Settings changed after a scan
- **WHEN** the user adds a source directory after a scan has finished
- **THEN** the result stays visible, a notice says the settings have changed since the scan, and no new scan starts

#### Scenario: Settings saved with the project
- **WHEN** the user closes the window after changing the directories or the linker file
- **THEN** the project holds the new settings as paths relative to the project directory

### Requirement: Findings Have A Fixed Severity
Every finding SHALL have a severity of error, warning or info, determined by its category as listed in the design. A finding inside an `#if` branch (marked possible) SHALL be one level lower, an info staying info. Severity SHALL only be used to order, colour and filter, and SHALL NOT change which findings are made.

#### Scenario: Category decides severity
- **WHEN** the result holds a missing mapping and a wildcard placement
- **THEN** the missing mapping is an error and the wildcard placement is info

#### Scenario: Data in flash is an error
- **WHEN** the result holds a data section placed in a flash region
- **THEN** that finding is an error

#### Scenario: Placement doubts are warnings
- **WHEN** the result holds a core data finding and a section selected by several regions
- **THEN** both are warnings

#### Scenario: Possible finding is one level lower
- **WHEN** a missing mapping is found inside an `#if` branch
- **THEN** it is a warning, and a wildcard placement found there stays info

#### Scenario: Filter by severity
- **WHEN** the user filters the diagnostics tab to errors
- **THEN** only findings of error severity are listed

### Requirement: Layout Tab Does Not Hide Findings Without A Section
The layout tab SHALL show, above the section tree and independent of its filters, a summary of the findings that belong to no output section (missing mapping, section declaration problem, repeated mapping and missing link symbol), with the count per severity and a control that switches to the diagnostics tab filtered to those categories. The filter "only rows with findings" SHALL keep concerning sections only.

#### Scenario: Summary stays while filtering
- **WHEN** the result has an unmapped section and a missing link symbol, and the user turns on "only rows with findings" in the layout tab
- **THEN** the summary still says that two findings belong to no output section, and offers to show them in the diagnostics tab

#### Scenario: No such findings
- **WHEN** every finding belongs to an output section
- **THEN** the layout tab shows no summary

### Requirement: Findings Located Across The Tabs
From a finding in the diagnostics tab the user SHALL be able to jump to the output section it belongs to in the layout tab, with the layout filters cleared. A finding that belongs to no output section SHALL have this control disabled with the reason given. From the findings listed in the details of a section in the layout tab the user SHALL be able to jump to the same finding in the diagnostics tab.

#### Scenario: Jump from diagnostics to layout
- **WHEN** the user selects a core data finding in the diagnostics tab and chooses to show it in the layout
- **THEN** the layout tab opens with the section of that finding selected

#### Scenario: Finding without a section
- **WHEN** the user selects a missing link symbol finding in the diagnostics tab
- **THEN** the control to show it in the layout is disabled and says that the finding belongs to no output section

#### Scenario: Jump from layout to diagnostics
- **WHEN** the user selects a finding in the details of a section in the layout tab and chooses to show it in the diagnostics
- **THEN** the diagnostics tab opens with that finding selected

### Requirement: Exports Keep Their Content
The diagnostics tab SHALL export the checklist and the layout tab SHALL export the layout as before, each following its tab's filters. The checklist header SHALL additionally list the number of findings per severity. The order and content of the checklist items SHALL be unchanged.

#### Scenario: Checklist header with counts
- **WHEN** the user exports the checklist of a result with two errors and one warning
- **THEN** the header lists two errors, one warning and no info, and the items are grouped by category as before

### Requirement: The Two Former Windows Are Replaced
The tools menu SHALL have one entry for the memory map window and SHALL NOT keep separate entries for the check and the layout. Opening it without a project SHALL tell the user to open a project first.

#### Scenario: One menu entry
- **WHEN** the user opens the tools menu
- **THEN** there is one entry for the memory map, not one for the check and one for the layout

#### Scenario: No project open
- **WHEN** the user chooses the entry without an open project
- **THEN** a message asks the user to open a project first

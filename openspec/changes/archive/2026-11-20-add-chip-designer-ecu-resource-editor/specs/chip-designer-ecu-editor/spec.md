## ADDED Requirements

### Requirement: ECU Resource Editor Page
The chip definition designer SHALL provide a page that lists a chip's ECU resources grouped by module and lets the user add, rename and delete modules and keys and change values, writing every accepted change to the chip's `ecu_resources`.

#### Scenario: Edit and save
- **WHEN** the user changes `OsResource.NumOfCores` to `4`, adds a key `Mcu.PllFreq` and saves the chip
- **THEN** loading the saved YAML gives `ecu_resources` containing both entries

#### Scenario: Any module can be created
- **WHEN** the user adds module `Gtm` and key `Tom0Channel0` with a list value
- **THEN** the chip stores `ecu_resources.Gtm.Tom0Channel0` as that list, without any code specific to the Gtm module

#### Scenario: Same limits as the loader
- **WHEN** the user enters a module name containing a dot, or a key whose value is a nested list
- **THEN** the editor shows an error naming the problem and leaves the chip's data unchanged

### Requirement: Value Editing By Shape
The editor SHALL edit scalars in a single line, lists item by item, and long multi-word strings in a multi-line field, keeping a leading space of a string value, and SHALL infer a typed scalar from the entered text with the same rules as `.properties` parsing while offering to keep the text as a string.

#### Scenario: Type inference
- **WHEN** the user types `0x10` into a scalar value
- **THEN** the stored value is the integer 16 and the editor shows the inferred type

#### Scenario: Keep as string
- **WHEN** the user types `007` and chooses to keep it as a string
- **THEN** the stored value is the string `007`

#### Scenario: Leading space of a string value
- **WHEN** a string value begins with one space, as in `Port.OutputModesXDMxx`
- **THEN** editing another key and saving leaves that value, including its leading space, unchanged

### Requirement: Search And Filter
The editor SHALL filter the key list by key name and by value text, and SHALL offer filters for entries still to be filled in and for entries with a problem.

#### Scenario: Search by key
- **WHEN** the user types `IsrTrigger`
- **THEN** only `Os.IsrTriggerMethodList` and other keys containing that text remain visible, each under its module

#### Scenario: Entries to fill in
- **WHEN** the user selects the "to fill in" filter
- **THEN** only entries whose value is still empty placeholders are shown

### Requirement: Index Range Editing Of Long Lists
The editor SHALL show a long list as index ranges (`<first>-<last>` and a value) and let the user edit them, expanding the result to the full list and rejecting gaps and overlaps, and SHALL decide the range notation used when saving only from the data, never from the view that was last used.

#### Scenario: Edit one range of a 992-element list
- **WHEN** the user changes the value of the range `16-18` in `Os.IsrTriggerMethodList`
- **THEN** exactly elements 16 to 18 change and the list still has 992 elements

#### Scenario: Gap is rejected
- **WHEN** the user edits the ranges so that index 40 is covered by no range
- **THEN** the editor reports `missing index 40` and keeps the previous list

#### Scenario: View does not change the value
- **WHEN** the user switches a list between the item view and the range view
- **THEN** the list value is identical before and after

### Requirement: Needed Keys Guidance
The editor SHALL scan the `.xdm` files and templates of one or more plugin directories, or of the loaded modules of the project the designer was opened from, for keys written as literals in `ecu:get` and `ecu:list`, list the keys that have no value for the chip together with the referencing modules, and let the user add selected keys as entries to fill in. The list SHALL state that only literal keys are scanned and SHALL NOT recommend keys that only other chips define.

#### Scenario: Missing key is listed and added
- **WHEN** a scanned xdm references `ecu:get('Mcu.PllFreq')` and the chip has no such key
- **THEN** the list shows `Mcu.PllFreq` with module `Mcu`, and adding it creates an entry with an empty value highlighted as to be filled in

#### Scenario: Existing and other-chip keys are not recommended
- **WHEN** a referenced key already has a value, or only another chip defines it
- **THEN** the key does not appear in the list of keys to add

#### Scenario: Built keys are not scanned
- **WHEN** a template builds a key by string concatenation
- **THEN** the key is not listed and the list states that such keys are not scanned

#### Scenario: Entries still to fill in at save time
- **WHEN** the user saves a chip that still has entries to fill in
- **THEN** the designer states how many there are and lets the user continue saving or go back

### Requirement: Consistency Hints In The Designer
The editor page and the preview page SHALL show the results of the ECU resource consistency rules for the chip being edited, and these hints SHALL NOT prevent saving.

#### Scenario: Count mismatch is shown
- **WHEN** `OsResource.NumOfCores` is `4` and `OsResource.AvailableCores` has three elements
- **THEN** both pages show the consistency warning and the chip can still be saved

### Requirement: Fallback Derivation Is Labelled
When a chip has no `ecu_resources`, the designer's `.properties` preview SHALL state that the values are fallback derivations and not authoritative data, and the derived `Adc.MaxResolution` SHALL equal the resolution chosen for the chip's ADC units.

#### Scenario: Label on the preview
- **WHEN** the preview page is opened for a chip without `ecu_resources`
- **THEN** the `.properties` preview begins with a note that the values are fallback derivations

#### Scenario: Resolution from the data
- **WHEN** the chip's ADC resolution is 10 bits and the preview is generated by the fallback derivation
- **THEN** `Adc.MaxResolution` is `10`

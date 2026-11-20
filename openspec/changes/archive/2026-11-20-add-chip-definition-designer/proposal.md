## Why

In semiconductor MCU toolchains, chip vendor engineers (AE/FAE/MCAL developers) regularly author hardware definitions for new derivatives (pins, packaging, alternate functions, peripheral capacities). Currently, these definitions must be created manually in raw YAML or text `.properties` files with thousands of lines, which is time-consuming and error-prone. Providing a graphical Chip Definition Designer with Excel/CSV pinout table import empowers both internal chip designers and tier-1 customers to rapidly model, clone, validate, and export MCU chip resources.

## What Changes

- Create a `PinoutTableImporter` service in `autosar_configurator/core/hardware/pinout_importer.py` supporting Excel (`.xlsx`) and CSV pinout tables with smart header mapping.
- Create a `ChipDefinitionExporter` in `autosar_configurator/core/hardware/chip_exporter.py` to serialize `GenericChipDefinition` to both standard YAML (`data/chips/<name>.yaml`) and EB Tresos `.properties` format.
- Implement `ChipDefinitionDesignerDialog` in `autosar_configurator/ui/dialogs/chip_definition_designer_dialog.py`:
  - Basic Info tab: Chip name, family, package, core count, description, and "Clone from Existing Chip" functionality.
  - Peripheral Capacities tab: CAN, ADC, SPI, and other hardware unit parameters.
  - Pinout & Multiplexing tab: Visual table for ports/pins/alternate functions with Excel/CSV import and add/delete controls.
  - Preview & Export tab: Live YAML and `.properties` generation, saving to chip database, and standalone export.
- Integrate the designer into `DaVinciMainWindow` under `Tools -> Chip Definition Designer...`.
- Integrate a "New Chip..." button into `HardwareMappingWizard` to allow seamless on-the-fly chip creation.
- Add comprehensive unit tests in `tests/core/test_chip_designer.py`.

## Impact

- Affected specs: `chip-management`
- Affected code:
  - `autosar_configurator/core/hardware/`
  - `autosar_configurator/ui/dialogs/`
  - `autosar_configurator/ui/wizards/hardware_mapping_wizard.py`
  - `autosar_configurator/ui/davinci_main_window.py`

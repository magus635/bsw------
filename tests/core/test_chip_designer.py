"""
Unit tests for PinoutTableImporter and ChipDefinitionExporter
"""
import pytest
from pathlib import Path
import tempfile
import csv

from autosar_configurator.core.hardware.chip_database import (
    ChipDefinition, PortPinDef, CanResourceDef, AdcResourceDef, SpiResourceDef, ChipDatabase
)
from autosar_configurator.core.hardware.pinout_importer import PinoutTableImporter
from autosar_configurator.core.hardware.chip_exporter import ChipDefinitionExporter


def test_import_pinout_from_csv(tmp_path: Path):
    """Test importing pinout from a CSV with standard column headers"""
    csv_file = tmp_path / "test_pins.csv"
    with open(csv_file, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(["Port", "Pin", "Pin Name", "Direction", "Alternate Functions"])
        writer.writerow(["PORT_A", "0", "PA0", "INPUT", "GPIO, ADC0_CH0, TIM0_CH0"])
        writer.writerow(["PORT_A", "1", "PA1", "INPUT", "GPIO, ADC0_CH1"])
        writer.writerow(["PORT_B", "4", "PB4", "OUTPUT", "GPIO, CAN1_TX"])

    importer = PinoutTableImporter()
    result = importer.import_file(csv_file)

    assert result.success is True
    assert result.total_pins == 3
    assert "PORT_A" in result.ports
    assert "PORT_B" in result.ports
    assert len(result.ports["PORT_A"]) == 2
    assert len(result.ports["PORT_B"]) == 1

    pa0 = result.ports["PORT_A"][0]
    assert pa0.name == "PA0"
    assert pa0.pin == 0
    assert pa0.default_direction == "INPUT"
    assert "ADC0_CH0" in pa0.alternate_functions
    assert "TIM0_CH0" in pa0.alternate_functions

    pb4 = result.ports["PORT_B"][0]
    assert pb4.name == "PB4"
    assert pb4.pin == 4
    assert pb4.default_direction == "OUTPUT"
    assert "CAN1_TX" in pb4.alternate_functions


def test_import_pinout_with_compound_names_and_af_columns(tmp_path: Path):
    """Test importing pinout where pin name has embedded port (PA0) and multiple AF columns"""
    csv_file = tmp_path / "test_compound.csv"
    with open(csv_file, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(["Signal Name", "Default Dir", "AF0", "AF1", "AF2"])
        writer.writerow(["PA0", "IN", "GPIO", "ADC0_CH0", "TIM0_CH0"])
        writer.writerow(["PB10", "OUT", "GPIO", "CAN0_TX", "-"])

    importer = PinoutTableImporter()
    result = importer.import_file(csv_file)

    assert result.success is True
    assert result.total_pins == 2
    assert "PORT_A" in result.ports
    assert "PORT_B" in result.ports

    pa0 = result.ports["PORT_A"][0]
    assert pa0.port == "PORT_A"
    assert pa0.pin == 0
    assert pa0.alternate_functions == ["GPIO", "ADC0_CH0", "TIM0_CH0"]

    pb10 = result.ports["PORT_B"][0]
    assert pb10.port == "PORT_B"
    assert pb10.pin == 10
    assert pb10.alternate_functions == ["GPIO", "CAN0_TX"]


def test_import_pinout_from_excel(tmp_path: Path):
    """Test importing pinout from an Excel file using openpyxl"""
    openpyxl = pytest.importorskip("openpyxl")

    xlsx_file = tmp_path / "test_pins.xlsx"
    wb = openpyxl.Workbook()
    ws = wb.active
    ws.title = "Pinout"

    ws.append(["端口", "引脚号", "引脚名称", "方向", "复用功能"])
    ws.append(["PORT_A", 0, "PA0", "INPUT", "GPIO, ADC0_CH0"])
    ws.append(["PORT_A", 4, "PA4", "OUTPUT", "GPIO, SPI0_MOSI"])
    ws.append(["PORT_B", 0, "PB0", "INPUT", "GPIO, ADC0_CH4"])
    wb.save(xlsx_file)
    wb.close()

    importer = PinoutTableImporter()
    result = importer.import_file(xlsx_file)

    assert result.success is True
    assert result.total_pins == 3
    assert len(result.ports["PORT_A"]) == 2
    assert len(result.ports["PORT_B"]) == 1
    assert result.ports["PORT_A"][1].name == "PA4"
    assert "SPI0_MOSI" in result.ports["PORT_A"][1].alternate_functions


def test_export_chip_yaml_and_roundtrip(tmp_path: Path):
    """Test exporting chip definition to YAML and loading it back with ChipDatabase"""
    chip = ChipDefinition(
        name="TEST_MCU_100",
        family="THA6",
        package="LQFP100",
        description="Test Chip for Designer"
    )
    chip.ports["PORT_A"] = [
        PortPinDef(name="PA0", port="PORT_A", pin=0, alternate_functions=["GPIO", "ADC0_CH0"], default_direction="INPUT"),
        PortPinDef(name="PA10", port="PORT_A", pin=10, alternate_functions=["GPIO", "CAN0_TX"], default_direction="OUTPUT"),
    ]
    chip.can_resources = [
        CanResourceDef(name="CAN0", controller_id=0, max_baudrate=1000000, supports_fd=True, mailbox_count=32)
    ]
    chip.adc_resources = [
        AdcResourceDef(name="ADC0", unit_id=0, channel_count=8, resolution_bits=12, channels=[0, 1, 2, 3, 4, 5, 6, 7])
    ]
    chip.spi_resources = [
        SpiResourceDef(name="SPI0", unit_id=0, max_baudrate=10000000, supports_dma=True)
    ]

    exporter = ChipDefinitionExporter()
    yaml_file = tmp_path / "TEST_MCU_100.yaml"
    exporter.save_yaml(chip, yaml_file)

    assert yaml_file.exists()

    # Load back using ChipDatabase
    db = ChipDatabase()
    loaded_chip = db._load_chip_from_yaml(yaml_file)

    assert loaded_chip is not None
    assert loaded_chip.name == "TEST_MCU_100"
    assert loaded_chip.package == "LQFP100"
    assert len(loaded_chip.ports["PORT_A"]) == 2
    assert loaded_chip.ports["PORT_A"][0].name == "PA0"
    assert "ADC0_CH0" in loaded_chip.ports["PORT_A"][0].alternate_functions
    assert len(loaded_chip.can_resources) == 1
    assert loaded_chip.can_resources[0].supports_fd is True
    assert len(loaded_chip.adc_resources) == 1
    assert loaded_chip.adc_resources[0].channels == [0, 1, 2, 3, 4, 5, 6, 7]


def test_export_properties_file(tmp_path: Path):
    """Test exporting chip definition to EB Tresos .properties file"""
    chip = ChipDefinition(
        name="TEST_MCU_100",
        family="THA6",
        package="LQFP100"
    )
    chip.ports["PORT_A"] = [
        PortPinDef(name="PA0", port="PORT_A", pin=0, alternate_functions=["GPIO", "ADC0_CH0"]),
        PortPinDef(name="PA15", port="PORT_A", pin=15, alternate_functions=["GPIO", "CAN0_TX"]),
    ]
    chip.can_resources = [
        CanResourceDef(name="CAN0", controller_id=0, max_baudrate=1000000),
        CanResourceDef(name="CAN1", controller_id=1, max_baudrate=1000000),
    ]
    chip.adc_resources = [
        AdcResourceDef(name="SARADC0", unit_id=0, channel_count=8),
        AdcResourceDef(name="SARADC1", unit_id=1, channel_count=8),
    ]

    exporter = ChipDefinitionExporter()
    prop_file = tmp_path / "CotexR52_TEST_MCU_100.properties"
    exporter.save_properties(chip, prop_file, num_cores=2, master_core="CORE0")

    assert prop_file.exists()
    content = prop_file.read_text(encoding="utf-8")

    assert "Resource.NumOfCores: 2" in content
    assert "Resource.MasterCore: CORE0" in content
    assert "Resource.SupportProcessor: TEST_MCU_100" in content
    assert "Port.MaxAvailablePortID: 1" in content
    assert "Port.MaxAvailablePinID: 15" in content
    assert "Can.MaxModules: 2" in content
    assert "Adc.HwUnitId: SARADC0, SARADC1" in content


def test_designer_dialog_init_and_clone(qtbot, tmp_path: Path, monkeypatch):
    """Test ChipDefinitionDesignerDialog initialization and cloning an existing chip"""
    from PySide6.QtWidgets import QMessageBox
    from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import ChipDefinitionDesignerDialog

    monkeypatch.setattr(QMessageBox, "information", lambda *args, **kwargs: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "warning", lambda *args, **kwargs: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "question", lambda *args, **kwargs: QMessageBox.Yes)

    # Create a dummy chip in db
    db = ChipDatabase()
    chip = ChipDefinition(name="CLONE_SRC", family="THA6", package="LQFP144", description="Source Chip")
    chip.ports["PORT_A"] = [PortPinDef(name="PA0", port="PORT_A", pin=0, alternate_functions=["GPIO", "CAN0_TX"])]
    db._chips["CLONE_SRC"] = chip

    dialog = ChipDefinitionDesignerDialog(chip_database=db)
    qtbot.addWidget(dialog)

    # Check initial values
    assert dialog.name_edit.text() == "NEW_MCU_SERIES"

    # Select clone template
    idx = dialog.clone_combo.findData("CLONE_SRC")
    assert idx != -1
    dialog.clone_combo.setCurrentIndex(idx)
    dialog._on_clone_clicked()

    assert dialog.name_edit.text() == "CLONE_SRC_COPY"
    assert dialog.family_edit.text() == "THA6"
    assert dialog.package_edit.text() == "LQFP144"
    assert len(dialog.current_ports["PORT_A"]) == 1
    assert dialog.current_ports["PORT_A"][0].name == "PA0"


def test_designer_dialog_preview_and_save(qtbot, tmp_path: Path, monkeypatch):
    """Test switching to preview tab and saving the chip"""
    from PySide6.QtWidgets import QMessageBox
    from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import ChipDefinitionDesignerDialog

    monkeypatch.setattr(QMessageBox, "information", lambda *args, **kwargs: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "warning", lambda *args, **kwargs: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "question", lambda *args, **kwargs: QMessageBox.Yes)

    db = ChipDatabase()
    dialog = ChipDefinitionDesignerDialog(chip_database=db)
    qtbot.addWidget(dialog)

    # Monkeypatch default data dir to tmp_path
    monkeypatch.setattr(dialog, "_get_default_data_dir", lambda: tmp_path)

    # Fill basic info
    dialog.name_edit.setText("MY_CUSTOM_CHIP")
    dialog.family_edit.setText("THA6")
    dialog.package_edit.setText("BGA256")

    # Add a pin
    dialog._on_add_pin_clicked()
    assert "PORT_A" in dialog.current_ports
    assert len(dialog.current_ports["PORT_A"]) == 1

    # Switch to Preview tab (index 3)
    dialog.tabs.setCurrentIndex(3)
    yaml_text = dialog.yaml_preview.toPlainText()
    assert "name: MY_CUSTOM_CHIP" in yaml_text
    assert "family: THA6" in yaml_text
    assert "package: BGA256" in yaml_text

    # Save
    saved_signal_received = []
    dialog.chip_saved.connect(lambda name: saved_signal_received.append(name))
    dialog._on_save_clicked()

    assert "MY_CUSTOM_CHIP" in saved_signal_received
    assert (tmp_path / "MY_CUSTOM_CHIP.yaml").exists()
    assert "MY_CUSTOM_CHIP" in db._chips

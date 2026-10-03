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


# ---------------------------------------------------------------------------
# Regression tests for designer review fixes
# ---------------------------------------------------------------------------
import yaml as _yaml
from autosar_configurator.core.hardware.chip_database import IntcSourceDef

REPO_CHIPS_DIR = Path(__file__).resolve().parents[2] / "autosar_configurator" / "data" / "chips"


def _rich_chip() -> ChipDefinition:
    chip = ChipDefinition(name="RICH_1", family="THA6", package="BGA", description='Quote "x" # not comment: yes')
    chip.ports["PORT_20"] = [
        PortPinDef(name="P20.2", port="PORT_20", pin=2, alternate_functions=["GPIO", "ETH:MDIO", "#TST", "[x]"],
                   default_direction="INOUT", alt_modes={0: "GPIO", 3: "ETH:MDIO"}),
    ]
    chip.intc_sources = [IntcSourceDef(name="IRQ_CAN0", vector_number=42, priority_bits=5, is_configurable=False)]
    chip.metadata = {"cpu_frequency": 400000000, "cores": {"count": 2, "available": ["CORE0", "CORE1"], "master": "CORE0"}}
    return chip


def test_yaml_export_escapes_special_characters_and_is_lossless(tmp_path: Path):
    chip = _rich_chip()
    path = tmp_path / "RICH_1.yaml"
    ChipDefinitionExporter().save_yaml(chip, path)

    _yaml.safe_load(path.read_text(encoding="utf-8"))  # must parse
    loaded = ChipDatabase(tmp_path).get_chip("RICH_1")
    assert loaded == chip


@pytest.mark.parametrize("yaml_file", sorted(REPO_CHIPS_DIR.glob("*.yaml")), ids=lambda p: p.stem)
def test_repo_chip_yaml_roundtrip(tmp_path: Path, yaml_file: Path):
    original = ChipDatabase()._load_chip_from_yaml(yaml_file)
    if original is None:
        pytest.skip("not a chip definition")
    ChipDefinitionExporter().save_yaml(original, tmp_path / f"{original.name}.yaml")
    assert ChipDatabase(tmp_path).get_chip(original.name) == original


@pytest.mark.parametrize("raw, expected", [
    ("INOUT", "INOUT"), ("In/Out", "INOUT"), ("I/O", "INOUT"), ("IO", "INOUT"), ("Bidirectional", "INOUT"),
    ("OUT", "OUTPUT"), ("Output", "OUTPUT"), ("IN", "INPUT"), ("input", "INPUT"),
])
def test_importer_direction_normalization(raw, expected):
    assert PinoutTableImporter._normalize_direction(raw) == expected


def test_importer_keeps_mode_numbers_across_empty_af_columns():
    rows = [
        ["Pin Name", "AF0", "AF1", "AF2", "AF3"],
        ["P20.2", "GPIO", "", "CAN0_TX", "SPI1_CS0 / SENT0"],
    ]
    result = PinoutTableImporter()._process_raw_table(rows)
    pin = result.ports["PORT_20"][0]
    assert pin.alt_modes == {0: "GPIO", 2: "CAN0_TX", 3: "SPI1_CS0/SENT0"}
    assert pin.alternate_functions == ["GPIO", "CAN0_TX", "SPI1_CS0", "SENT0"]


def test_importer_mode_numbers_follow_header_digits_not_column_order():
    rows = [["Pin Name", "MUX1", "MUX2", "MUX5"], ["P0.1", "UART0_TX", "", "PWM3"]]
    pin = PinoutTableImporter()._process_raw_table(rows).ports["PORT_0"][0]
    assert pin.alt_modes == {1: "UART0_TX", 5: "PWM3"}


def test_importer_duplicate_pins_counted_once():
    rows = [["Pin Name", "Direction"], ["P20.2", "IN"], ["P20.2", "OUT"], ["P20.3", "IN"]]
    result = PinoutTableImporter()._process_raw_table(rows)
    assert result.total_pins == 2
    assert result.ports["PORT_20"][0].default_direction == "OUTPUT"
    assert any("Duplicate" in w for w in result.warnings)


def test_importer_warns_on_missing_sheet(tmp_path: Path):
    openpyxl = pytest.importorskip("openpyxl")
    wb = openpyxl.Workbook()
    wb.active.title = "Pins"
    wb.active.append(["Pin Name", "AF0"])
    wb.active.append(["P1.0", "GPIO"])
    path = tmp_path / "pins.xlsx"
    wb.save(path)
    result = PinoutTableImporter().import_file(path, sheet_name="Missing")
    assert result.success
    assert "Missing" in result.warnings[0]


# --- Dialog -----------------------------------------------------------------

@pytest.fixture
def silent_boxes(monkeypatch):
    from PySide6.QtWidgets import QMessageBox
    calls = {"question": QMessageBox.Yes, "warnings": []}
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **k: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "critical", lambda *a, **k: QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "warning", lambda *a, **k: calls["warnings"].append(a[2]) or QMessageBox.Ok)
    monkeypatch.setattr(QMessageBox, "question", lambda *a, **k: calls["question"])
    return calls


def _make_dialog(qtbot, db):
    from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import ChipDefinitionDesignerDialog
    dialog = ChipDefinitionDesignerDialog(chip_database=db)
    qtbot.addWidget(dialog)
    return dialog


def _model_cell(dialog, port, pin, col):
    model = dialog.pin_model
    row = next(i for i, p in enumerate(model.pins()) if p.port == port and p.pin == pin)
    return model.index(row, col)


def test_dialog_edits_survive_filter_add_and_delete(qtbot, silent_boxes):
    from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import PinTableModel
    db = ChipDatabase()
    db.register_chip(_rich_chip())
    dialog = _make_dialog(qtbot, db)
    dialog._load_chip_by_name("RICH_1")

    assert dialog.pin_model.setData(_model_cell(dialog, "PORT_20", 2, PinTableModel.COL_NAME), "RENAMED")
    dialog.port_filter_combo.setCurrentText("PORT_20")
    dialog._on_add_pin_clicked()
    dialog.port_filter_combo.setCurrentIndex(0)

    names = [p.name for p in dialog.current_ports["PORT_20"]]
    assert "RENAMED" in names and len(names) == 2


def test_dialog_changing_pin_id_does_not_leave_ghost_pin(qtbot, silent_boxes):
    from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import PinTableModel
    db = ChipDatabase()
    db.register_chip(_rich_chip())
    dialog = _make_dialog(qtbot, db)
    dialog._load_chip_by_name("RICH_1")

    assert dialog.pin_model.setData(_model_cell(dialog, "PORT_20", 2, PinTableModel.COL_PIN), "7")
    assert [p.pin for p in dialog.current_ports["PORT_20"]] == [7]
    assert not dialog.pin_model.setData(_model_cell(dialog, "PORT_20", 7, PinTableModel.COL_PIN), "abc")
    assert not dialog.pin_model.setData(_model_cell(dialog, "PORT_20", 7, PinTableModel.COL_DIR), "sideways")


def test_dialog_functions_column_roundtrips_mode_numbers(qtbot, silent_boxes):
    from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import PinTableModel
    db = ChipDatabase()
    db.register_chip(_rich_chip())
    dialog = _make_dialog(qtbot, db)
    dialog._load_chip_by_name("RICH_1")

    idx = _model_cell(dialog, "PORT_20", 2, PinTableModel.COL_FUNCS)
    assert dialog.pin_model.data(idx) == "0:GPIO, 3:ETH:MDIO"
    dialog.pin_model.setData(idx, "0:GPIO, 5:CAN1_RX")
    pin = dialog.current_ports["PORT_20"][0]
    assert pin.alt_modes == {0: "GPIO", 5: "CAN1_RX"}
    assert pin.alternate_functions == ["GPIO", "CAN1_RX"]


def test_dialog_duplicate_pins_block_save(qtbot, tmp_path, silent_boxes):
    db = ChipDatabase(tmp_path)
    dialog = _make_dialog(qtbot, db)
    dialog.name_edit.setText("DUP_CHIP")
    dialog._on_add_pin_clicked()
    dialog._on_add_pin_clicked()
    from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import PinTableModel
    dialog.pin_model.setData(dialog.pin_model.index(1, PinTableModel.COL_PIN), "0")

    dialog._on_save_clicked()
    assert not (tmp_path / "DUP_CHIP.yaml").exists()
    assert any("PORT_A/0" in w for w in silent_boxes["warnings"])


def test_dialog_clone_and_save_preserves_intc_and_metadata(qtbot, tmp_path, silent_boxes):
    db = ChipDatabase(tmp_path)
    db.register_chip(_rich_chip())
    dialog = _make_dialog(qtbot, db)
    dialog.clone_combo.setCurrentIndex(dialog.clone_combo.findData("RICH_1"))
    dialog._on_clone_clicked()
    dialog._on_save_clicked()

    saved = ChipDatabase(tmp_path).get_chip("RICH_1_COPY")
    assert saved.intc_sources == _rich_chip().intc_sources
    assert saved.metadata["cpu_frequency"] == 400000000
    assert saved.metadata["cores"]["count"] == 2
    assert saved.ports["PORT_20"][0].alt_modes == {0: "GPIO", 3: "ETH:MDIO"}


def test_dialog_load_resets_peripheral_tables(qtbot, silent_boxes):
    db = ChipDatabase()
    with_can = ChipDefinition(name="WITH_CAN")
    with_can.can_resources = [CanResourceDef(name=f"CAN{i}", controller_id=i) for i in range(3)]
    db.register_chip(with_can)
    db.register_chip(ChipDefinition(name="NO_CAN"))
    dialog = _make_dialog(qtbot, db)

    dialog._load_chip_by_name("WITH_CAN")
    assert dialog.can_table.rowCount() == 3
    dialog._load_chip_by_name("NO_CAN")
    assert dialog.can_table.rowCount() == 0
    assert dialog._build_current_chip().can_resources == []


def test_dialog_save_rejects_unsafe_name(qtbot, tmp_path, silent_boxes):
    dialog = _make_dialog(qtbot, ChipDatabase(tmp_path))
    dialog.name_edit.setText("../evil")
    dialog._on_save_clicked()
    assert not list(tmp_path.parent.glob("evil.yaml"))
    assert silent_boxes["warnings"]


def test_dialog_save_asks_before_overwriting_other_chip(qtbot, tmp_path, silent_boxes):
    from PySide6.QtWidgets import QMessageBox
    ChipDefinitionExporter().save_yaml(ChipDefinition(name="EXISTING", description="orig"), tmp_path / "EXISTING.yaml")
    db = ChipDatabase(tmp_path)
    dialog = _make_dialog(qtbot, db)
    dialog.name_edit.setText("EXISTING")
    dialog._on_add_pin_clicked()

    silent_boxes["question"] = QMessageBox.No
    dialog._on_save_clicked()
    assert ChipDatabase(tmp_path).get_chip("EXISTING").description == "orig"

    silent_boxes["question"] = QMessageBox.Yes
    dialog._on_save_clicked()
    assert ChipDatabase(tmp_path).get_chip("EXISTING").description != "orig"


def test_dialog_saves_into_database_dir_and_close_reports_accepted(qtbot, tmp_path, silent_boxes):
    from PySide6.QtWidgets import QDialog
    db = ChipDatabase(tmp_path)
    dialog = _make_dialog(qtbot, db)
    dialog.name_edit.setText("SAVED_CHIP")
    dialog._on_add_pin_clicked()
    dialog._on_save_clicked()

    assert (tmp_path / "SAVED_CHIP.yaml").exists()
    saved = db.get_chip("SAVED_CHIP")
    dialog._on_add_pin_clicked()  # editing after save must not mutate the DB copy
    assert len(saved.get_all_pins()) == 1

    dialog.reject()
    assert dialog.result() == QDialog.Accepted


def test_dialog_add_pin_picks_existing_port_when_on_all_ports(qtbot, silent_boxes):
    from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import ALL_PORTS_LABEL
    db = ChipDatabase()
    custom_chip = ChipDefinition(name="NUMERIC_PORTS")
    custom_chip.ports["PORT_0"] = [PortPinDef(name="P0_0", port="PORT_0", pin=0, alternate_functions=["GPIO"])]
    db.register_chip(custom_chip)

    dialog = _make_dialog(qtbot, db)
    dialog._load_chip_by_name("NUMERIC_PORTS")
    dialog.port_filter_combo.setCurrentText(ALL_PORTS_LABEL)

    dialog._on_add_pin_clicked()
    all_pins = dialog.pin_model.pins()
    assert len(all_pins) == 2
    # Second pin must be in PORT_0, not PORT_A
    assert all_pins[1].port == "PORT_0"
    assert all_pins[1].pin == 1


def test_dialog_new_chip_has_baseline_metadata(qtbot, silent_boxes):
    dialog = _make_dialog(qtbot, ChipDatabase())
    chip = dialog._build_current_chip()
    assert "cpu_frequency" in chip.metadata
    assert "flash_size" in chip.metadata
    assert "ram_size" in chip.metadata
    assert chip.metadata["cores"]["count"] == 2


def test_model_batch_remove_rows(qtbot):
    from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import PinTableModel
    model = PinTableModel()
    model.set_pins([
        PortPinDef(name=f"P{i}", port="PORT_0", pin=i, alternate_functions=["GPIO"])
        for i in range(5)
    ])
    assert model.rowCount() == 5

    # Delete 3 non-contiguous rows in batch
    model.remove_rows([0, 2, 4])
    assert model.rowCount() == 2
    remaining_pins = [p.pin for p in model.pins()]
    assert remaining_pins == [1, 3]


def test_parse_int_handles_underscores_and_whitespace():
    from autosar_configurator.ui.dialogs.chip_definition_designer_dialog import _parse_int
    assert _parse_int(" 10_000_000 ", default=1000) == 10000000
    assert _parse_int("bad", default=5000) == 5000
    assert _parse_int(None, default=42) == 42
    assert _parse_int(8000, default=0) == 8000

"""
Import Wizard
Import configuration data from CSV, Excel, or DBC files
"""
from enum import Enum
from pathlib import Path
from typing import Dict, Any, Optional, List

from PySide6.QtWidgets import (
    QVBoxLayout, QHBoxLayout, QLabel, QComboBox, QLineEdit,
    QFormLayout, QPushButton, QTextEdit, QTableWidget,
    QTableWidgetItem, QHeaderView, QGroupBox, QFileDialog,
    QProgressBar, QWidget, QCheckBox, QRadioButton, QButtonGroup
)
from PySide6.QtCore import Qt, Signal, QThread

from .wizard_base import ConfigWizard, WizardPage
from ...core.model.definition_model import EcucModuleDef, EcucContainerDef
from ...core.model.configuration_model import EcucContainerValue
from ...core.config_manager import ConfigurationManager
from ...core.importers import BaseImporter, ImportResult, CsvImporter, ExcelImporter, DbcImporter


class ImportFormat(Enum):
    """Supported import formats"""
    CSV = "CSV (Comma-Separated Values)"
    EXCEL = "Excel Workbook (.xlsx)"
    DBC = "DBC (CAN Database)"


class ImportSourcePage(WizardPage):
    """Page 1: Select import file"""

    file_selected = Signal(str)  # File path

    def __init__(self):
        self.file_path_edit = QLineEdit()
        self.format_combo = QComboBox()
        self.browse_btn = QPushButton()
        self.file_info_label = QLabel()
        self.importer: Optional[BaseImporter] = None

        super().__init__(
            "Select Source File",
            "Choose the file to import configuration from"
        )

    def _setup_ui(self):
        # Format selection
        format_group = QGroupBox("File Format")
        format_layout = QVBoxLayout()

        self.format_combo.addItem(ImportFormat.CSV.value, ImportFormat.CSV)
        self.format_combo.addItem(ImportFormat.EXCEL.value, ImportFormat.EXCEL)
        self.format_combo.addItem(ImportFormat.DBC.value, ImportFormat.DBC)
        self.format_combo.currentIndexChanged.connect(self._on_format_changed)

        format_layout.addWidget(self.format_combo)
        format_group.setLayout(format_layout)
        self.layout.addWidget(format_group)

        # File selection
        file_group = QGroupBox("Source File")
        file_layout = QVBoxLayout()

        path_layout = QHBoxLayout()
        self.file_path_edit.setPlaceholderText("Select a file...")
        self.file_path_edit.setReadOnly(True)
        path_layout.addWidget(self.file_path_edit)

        self.browse_btn = QPushButton("Browse...")
        self.browse_btn.clicked.connect(self._browse_file)
        path_layout.addWidget(self.browse_btn)

        file_layout.addLayout(path_layout)

        self.file_info_label.setStyleSheet("color: gray;")
        self.file_info_label.setWordWrap(True)
        file_layout.addWidget(self.file_info_label)

        file_group.setLayout(file_layout)
        self.layout.addWidget(file_group)

        self.layout.addStretch()

        # Initialize importer
        self._on_format_changed()

    def _on_format_changed(self):
        """Handle format selection change"""
        format_type = self.format_combo.currentData()

        if format_type == ImportFormat.CSV:
            self.importer = CsvImporter()
        elif format_type == ImportFormat.EXCEL:
            self.importer = ExcelImporter()
        elif format_type == ImportFormat.DBC:
            self.importer = DbcImporter()

        # Clear current file if format changed
        if self.file_path_edit.text():
            self._validate_file()

    def _browse_file(self):
        """Open file browser"""
        format_type = self.format_combo.currentData()

        if format_type == ImportFormat.CSV:
            filter_str = "CSV Files (*.csv *.txt);;All Files (*)"
        elif format_type == ImportFormat.EXCEL:
            filter_str = "Excel Files (*.xlsx *.xlsm);;All Files (*)"
        elif format_type == ImportFormat.DBC:
            filter_str = "DBC Files (*.dbc);;All Files (*)"
        else:
            filter_str = "All Files (*)"

        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Select Import File",
            "",
            filter_str
        )

        if file_path:
            self.file_path_edit.setText(file_path)
            self._validate_file()
            self.file_selected.emit(file_path)

    def _validate_file(self):
        """Validate selected file"""
        file_path = self.file_path_edit.text()
        if not file_path:
            self.file_info_label.setText("")
            return

        path = Path(file_path)
        if not path.exists():
            self.file_info_label.setText("File not found")
            self.file_info_label.setStyleSheet("color: red;")
            return

        if self.importer:
            valid, error = self.importer.validate_file(path)
            if valid:
                # Get additional info
                columns = self.importer.get_columns(path)
                size = path.stat().st_size
                size_str = f"{size / 1024:.1f} KB" if size > 1024 else f"{size} bytes"

                self.file_info_label.setText(
                    f"Valid file ({size_str})\n"
                    f"Columns/Fields: {len(columns)}"
                )
                self.file_info_label.setStyleSheet("color: green;")
            else:
                self.file_info_label.setText(f"Validation failed: {error}")
                self.file_info_label.setStyleSheet("color: red;")

        self.completeChanged.emit()

    def get_data(self) -> Dict[str, Any]:
        return {
            "file_path": self.file_path_edit.text(),
            "format": self.format_combo.currentData(),
            "importer": self.importer
        }

    def isComplete(self) -> bool:
        file_path = self.file_path_edit.text()
        if not file_path:
            return False

        path = Path(file_path)
        if not path.exists():
            return False

        if self.importer:
            valid, _ = self.importer.validate_file(path)
            return valid

        return False


class ColumnMappingPage(WizardPage):
    """Page 2: Map source columns to target parameters"""

    def __init__(self, config_manager: ConfigurationManager):
        self.config_manager = config_manager
        self.mapping_table = QTableWidget()
        self.container_combo = QComboBox()

        super().__init__(
            "Column Mapping",
            "Map source columns to AUTOSAR parameters"
        )

    def _setup_ui(self):
        # Target container selection
        container_group = QGroupBox("Target Container")
        container_layout = QVBoxLayout()
        container_layout.addWidget(self.container_combo)
        container_group.setLayout(container_layout)
        self.layout.addWidget(container_group)

        # Mapping table
        mapping_group = QGroupBox("Column to Parameter Mapping")
        mapping_layout = QVBoxLayout()

        self.mapping_table.setColumnCount(3)
        self.mapping_table.setHorizontalHeaderLabels([
            "Source Column", "Target Parameter", "Include"
        ])

        header = self.mapping_table.horizontalHeader()
        header.setSectionResizeMode(0, QHeaderView.Stretch)
        header.setSectionResizeMode(1, QHeaderView.Stretch)
        header.setSectionResizeMode(2, QHeaderView.ResizeToContents)

        mapping_layout.addWidget(self.mapping_table)
        mapping_group.setLayout(mapping_layout)
        self.layout.addWidget(mapping_group)

    def initializePage(self):
        """Populate mapping table"""
        wizard = self.wizard()

        # Get source data
        source_data = {}
        if hasattr(wizard, 'source_page'):
            source_data = wizard.source_page.get_data()

        file_path = source_data.get("file_path")
        importer = source_data.get("importer")

        if not file_path or not importer:
            return

        path = Path(file_path)

        # Populate container combo
        self.container_combo.clear()
        if self.config_manager and hasattr(self.config_manager, 'module_def'):
            module_def = self.config_manager.module_def
            if module_def:
                for container_def in module_def.containers.values():
                    if container_def.upper_multiplicity != 1:  # Allow multiple
                        self.container_combo.addItem(
                            container_def.short_name,
                            container_def
                        )

        # Get columns from source
        columns = importer.get_columns(path)

        # Clear and populate mapping table
        self.mapping_table.setRowCount(len(columns))

        for row, column in enumerate(columns):
            # Source column (read-only)
            src_item = QTableWidgetItem(column)
            src_item.setFlags(src_item.flags() & ~Qt.ItemIsEditable)
            self.mapping_table.setItem(row, 0, src_item)

            # Target parameter (combo)
            target_combo = QComboBox()
            target_combo.addItem("(Do not import)", None)

            # Add parameters from selected container
            container_def = self.container_combo.currentData()
            if container_def:
                for param_name in container_def.parameters.keys():
                    target_combo.addItem(param_name, param_name)

            # Try auto-matching by name
            for i in range(target_combo.count()):
                item_text = target_combo.itemText(i)
                if item_text and (
                    item_text.lower() == column.lower() or
                    column.lower() in item_text.lower() or
                    item_text.lower() in column.lower()
                ):
                    target_combo.setCurrentIndex(i)
                    break

            self.mapping_table.setCellWidget(row, 1, target_combo)

            # Include checkbox
            include_check = QCheckBox()
            include_check.setChecked(target_combo.currentData() is not None)

            # Link checkbox to combo
            target_combo.currentIndexChanged.connect(
                lambda idx, cb=include_check, tc=target_combo:
                cb.setChecked(tc.currentData() is not None)
            )

            include_widget = QWidget()
            include_layout = QHBoxLayout(include_widget)
            include_layout.addWidget(include_check)
            include_layout.setAlignment(Qt.AlignCenter)
            include_layout.setContentsMargins(0, 0, 0, 0)
            self.mapping_table.setCellWidget(row, 2, include_widget)

        # Connect container change to refresh mappings
        self.container_combo.currentIndexChanged.connect(self._refresh_parameter_options)

    def _refresh_parameter_options(self):
        """Refresh parameter options when container changes"""
        container_def = self.container_combo.currentData()
        if not container_def:
            return

        for row in range(self.mapping_table.rowCount()):
            target_combo = self.mapping_table.cellWidget(row, 1)
            if isinstance(target_combo, QComboBox):
                current_text = target_combo.currentText()

                target_combo.clear()
                target_combo.addItem("(Do not import)", None)

                for param_name in container_def.parameters.keys():
                    target_combo.addItem(param_name, param_name)

                # Try to restore selection
                idx = target_combo.findText(current_text)
                if idx >= 0:
                    target_combo.setCurrentIndex(idx)

    def get_data(self) -> Dict[str, Any]:
        """Get column mapping"""
        mapping = {}

        for row in range(self.mapping_table.rowCount()):
            src_item = self.mapping_table.item(row, 0)
            target_combo = self.mapping_table.cellWidget(row, 1)
            include_widget = self.mapping_table.cellWidget(row, 2)

            if not src_item or not target_combo:
                continue

            include_check = include_widget.findChild(QCheckBox)
            if not include_check or not include_check.isChecked():
                continue

            target_param = target_combo.currentData()
            if target_param:
                mapping[src_item.text()] = target_param

        return {
            "column_mapping": mapping,
            "container_def": self.container_combo.currentData()
        }


class ImportPreviewPage(WizardPage):
    """Page 3: Preview imported data"""

    def __init__(self):
        self.preview_table = QTableWidget()
        self.stats_label = QLabel()

        super().__init__(
            "Preview Import",
            "Review the data that will be imported"
        )

    def _setup_ui(self):
        # Stats
        self.stats_label.setStyleSheet("font-weight: bold;")
        self.layout.addWidget(self.stats_label)

        # Preview table
        self.preview_table.setAlternatingRowColors(True)
        self.layout.addWidget(self.preview_table)

    def initializePage(self):
        """Generate preview"""
        wizard = self.wizard()

        source_data = {}
        mapping_data = {}

        if hasattr(wizard, 'source_page'):
            source_data = wizard.source_page.get_data()

        if hasattr(wizard, 'mapping_page'):
            mapping_data = wizard.mapping_page.get_data()

        file_path = source_data.get("file_path")
        importer = source_data.get("importer")
        column_mapping = mapping_data.get("column_mapping", {})

        if not file_path or not importer or not column_mapping:
            self.stats_label.setText("No data to preview")
            return

        path = Path(file_path)

        # Get preview data
        preview_records = importer.preview(path, limit=20)

        # Setup table columns
        target_params = list(column_mapping.values())
        self.preview_table.setColumnCount(len(target_params))
        self.preview_table.setHorizontalHeaderLabels(target_params)

        # Populate preview
        self.preview_table.setRowCount(len(preview_records))

        for row, record in enumerate(preview_records):
            for col, (src_col, target_param) in enumerate(column_mapping.items()):
                value = record.get(src_col, "")
                item = QTableWidgetItem(str(value))
                self.preview_table.setItem(row, col, item)

        # Update stats
        self.stats_label.setText(
            f"Showing first {len(preview_records)} records "
            f"({len(target_params)} parameters mapped)"
        )

        # Auto-resize columns
        self.preview_table.resizeColumnsToContents()

    def get_data(self) -> Dict[str, Any]:
        return {}


class ImportProgressPage(WizardPage):
    """Page 4: Import progress and results"""

    def __init__(self, config_manager: ConfigurationManager):
        self.config_manager = config_manager
        self.progress_bar = QProgressBar()
        self.result_text = QTextEdit()
        self.import_result: Optional[ImportResult] = None

        super().__init__(
            "Import Progress",
            "Importing configuration data"
        )

    def _setup_ui(self):
        self.progress_bar.setMinimum(0)
        self.progress_bar.setMaximum(100)
        self.layout.addWidget(self.progress_bar)

        self.result_text.setReadOnly(True)
        self.layout.addWidget(self.result_text)

    def initializePage(self):
        """Perform import"""
        wizard = self.wizard()

        source_data = {}
        mapping_data = {}

        if hasattr(wizard, 'source_page'):
            source_data = wizard.source_page.get_data()

        if hasattr(wizard, 'mapping_page'):
            mapping_data = wizard.mapping_page.get_data()

        file_path = source_data.get("file_path")
        importer = source_data.get("importer")
        column_mapping = mapping_data.get("column_mapping", {})
        container_def = mapping_data.get("container_def")

        if not file_path or not importer or not column_mapping:
            self.result_text.setPlainText("Import failed: Missing configuration")
            return

        path = Path(file_path)

        # Perform import
        self.progress_bar.setValue(10)
        self.result_text.setPlainText("Starting import...")

        try:
            self.import_result = importer.import_data(path, column_mapping)
            self.progress_bar.setValue(50)

            # Create container instances
            created_count = 0
            if container_def and self.import_result.success:
                for record in self.import_result.imported_data:
                    try:
                        instance = self.config_manager.create_container_instance(
                            container_def
                        )

                        # Set parameter values
                        for param_name, value in record.items():
                            if param_name.startswith('_'):
                                continue  # Skip internal fields
                            try:
                                self.config_manager.set_parameter_value(
                                    instance, param_name, value
                                )
                            except Exception as e:
                                self.import_result.warnings.append(
                                    f"Failed to set {param_name}: {e}"
                                )

                        created_count += 1
                    except Exception as e:
                        self.import_result.errors.append(
                            f"Failed to create instance: {e}"
                        )

            self.progress_bar.setValue(100)

            # Display results
            result_text = f"Import Complete\n"
            result_text += "=" * 50 + "\n\n"
            result_text += f"Records imported: {self.import_result.records_imported}\n"
            result_text += f"Records skipped: {self.import_result.records_skipped}\n"
            result_text += f"Instances created: {created_count}\n\n"

            if self.import_result.errors:
                result_text += f"Errors ({len(self.import_result.errors)}):\n"
                for error in self.import_result.errors[:10]:  # Limit display
                    result_text += f"  - {error}\n"
                if len(self.import_result.errors) > 10:
                    result_text += f"  ... and {len(self.import_result.errors) - 10} more\n"
                result_text += "\n"

            if self.import_result.warnings:
                result_text += f"Warnings ({len(self.import_result.warnings)}):\n"
                for warning in self.import_result.warnings[:10]:
                    result_text += f"  - {warning}\n"
                if len(self.import_result.warnings) > 10:
                    result_text += f"  ... and {len(self.import_result.warnings) - 10} more\n"

            self.result_text.setPlainText(result_text)

        except Exception as e:
            self.progress_bar.setValue(100)
            self.result_text.setPlainText(f"Import failed:\n{str(e)}")
            self.import_result = ImportResult(success=False, errors=[str(e)])

    def get_data(self) -> Dict[str, Any]:
        return {
            "import_result": self.import_result
        }


class ImportWizard(ConfigWizard):
    """Wizard for importing configuration data"""

    def __init__(self, config_manager: ConfigurationManager,
                 parent_instance: Optional[EcucContainerValue] = None,
                 parent=None):
        self.config_manager = config_manager
        self.parent_instance = parent_instance
        self.import_result: Optional[ImportResult] = None

        super().__init__(parent, "Import Configuration Wizard")
        self.setMinimumSize(800, 600)

    def _setup_pages(self):
        """Setup wizard pages"""
        # Page 1: Source file selection
        self.source_page = ImportSourcePage()
        self.addPage(self.source_page)

        # Page 2: Column mapping
        self.mapping_page = ColumnMappingPage(self.config_manager)
        self.addPage(self.mapping_page)

        # Page 3: Preview
        self.preview_page = ImportPreviewPage()
        self.addPage(self.preview_page)

        # Page 4: Progress
        self.progress_page = ImportProgressPage(self.config_manager)
        self.addPage(self.progress_page)

    def accept(self):
        """Complete import"""
        # Get result from progress page
        progress_data = self.progress_page.get_data()
        self.import_result = progress_data.get("import_result")

        if self.import_result:
            self.wizard_completed.emit({
                "success": self.import_result.success,
                "records_imported": self.import_result.records_imported,
                "records_skipped": self.import_result.records_skipped,
                "errors": self.import_result.errors,
                "warnings": self.import_result.warnings
            })
        else:
            self.wizard_completed.emit({
                "success": False,
                "records_imported": 0
            })

        super().accept()

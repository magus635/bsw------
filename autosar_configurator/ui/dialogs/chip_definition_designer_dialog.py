"""
Chip Definition Designer Dialog

A graphical interface for semiconductor chip engineers and ECU integrators
to author, edit, clone, validate, and export MCU chip hardware definitions.
"""
from pathlib import Path
from typing import Dict, List, Optional, Any
import logging

from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QFormLayout, QLineEdit,
    QTextEdit, QLabel, QGroupBox, QWidget, QComboBox, QPushButton,
    QSpinBox, QCheckBox, QTabWidget, QTableWidget, QTableWidgetItem,
    QHeaderView, QMessageBox, QFileDialog, QSplitter, QAbstractItemView
)
from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QFont, QGuiApplication

from ...core.hardware.chip_database import (
    ChipDatabase, ChipDefinition, PortPinDef,
    CanResourceDef, AdcResourceDef, SpiResourceDef
)
from ...core.hardware.pinout_importer import PinoutTableImporter
from ...core.hardware.chip_exporter import ChipDefinitionExporter

logger = logging.getLogger(__name__)


class ChipDefinitionDesignerDialog(QDialog):
    """Graphical designer for MCU chip hardware resource definitions"""

    chip_saved = Signal(str)  # Emits chip_name when successfully saved

    def __init__(self, chip_database: Optional[ChipDatabase] = None, initial_chip: Optional[str] = None, parent=None):
        super().__init__(parent)
        self.chip_database = chip_database or ChipDatabase(self._get_default_data_dir())
        self.exporter = ChipDefinitionExporter()
        self.importer = PinoutTableImporter()

        # In-memory working copy
        self.current_ports: Dict[str, List[PortPinDef]] = {}
        self._last_saved_chip: Optional[str] = None

        self.setWindowTitle("Chip Definition Designer - 芯片定义设计器")
        self.resize(920, 700)
        self.setMinimumWidth(800)
        self.setMinimumHeight(600)

        self._setup_ui()
        self._populate_clone_dropdown()

        if initial_chip:
            self._load_chip_by_name(initial_chip)
        else:
            self._init_default_fields()

    def _get_default_data_dir(self) -> Path:
        """Locate default data/chips directory"""
        pkg_dir = Path(__file__).resolve().parent.parent.parent
        data_dir = pkg_dir / "data" / "chips"
        data_dir.mkdir(parents=True, exist_ok=True)
        return data_dir

    def _setup_ui(self):
        """Construct multi-tab UI"""
        main_layout = QVBoxLayout(self)
        main_layout.setContentsMargins(12, 12, 12, 12)
        main_layout.setSpacing(10)

        # Top bar: Clone toolbar
        clone_bar = QGroupBox("快速模板 (Quick Template)")
        clone_layout = QHBoxLayout(clone_bar)
        clone_layout.setContentsMargins(10, 6, 10, 6)

        clone_layout.addWidget(QLabel("从已有芯片克隆 (Clone Existing):"))
        self.clone_combo = QComboBox()
        self.clone_combo.setMinimumWidth(220)
        clone_layout.addWidget(self.clone_combo)

        clone_btn = QPushButton("📋 克隆并载入 (Clone & Apply)")
        clone_btn.clicked.connect(self._on_clone_clicked)
        clone_layout.addWidget(clone_btn)
        clone_layout.addStretch()

        main_layout.addWidget(clone_bar)

        # Tabs
        self.tabs = QTabWidget()
        self.tabs.currentChanged.connect(self._on_tab_changed)
        main_layout.addWidget(self.tabs, 1)

        # Setup individual tabs
        self._setup_basic_tab()
        self._setup_peripherals_tab()
        self._setup_pinout_tab()
        self._setup_preview_tab()

        # Bottom Button Bar
        bottom_bar = QHBoxLayout()
        bottom_bar.setContentsMargins(0, 4, 0, 0)

        self.status_label = QLabel("就绪")
        self.status_label.setStyleSheet("color: #666; font-size: 12px;")
        bottom_bar.addWidget(self.status_label)
        bottom_bar.addStretch()

        save_btn = QPushButton("💾 保存到芯片库 (Save to Database)")
        save_btn.setStyleSheet("font-weight: bold; padding: 6px 14px;")
        save_btn.clicked.connect(self._on_save_clicked)
        bottom_bar.addWidget(save_btn)

        close_btn = QPushButton("关闭 (Close)")
        close_btn.clicked.connect(self.reject)
        bottom_bar.addWidget(close_btn)

        main_layout.addLayout(bottom_bar)

    def _setup_basic_tab(self):
        """Tab 1: Basic Chip Metadata"""
        tab = QWidget()
        layout = QVBoxLayout(tab)
        layout.setContentsMargins(14, 14, 14, 14)

        form_group = QGroupBox("芯片基本规格 (Basic Specifications)")
        form = QFormLayout(form_group)
        form.setLabelAlignment(Qt.AlignRight)
        form.setFieldGrowthPolicy(QFormLayout.ExpandingFieldsGrow)
        form.setHorizontalSpacing(12)
        form.setVerticalSpacing(10)

        self.name_edit = QLineEdit()
        self.name_edit.setPlaceholderText("例: THA610X_LFBGA180")
        form.addRow("芯片型号 (Name)*:", self.name_edit)

        self.family_edit = QLineEdit()
        self.family_edit.setPlaceholderText("例: THA6")
        form.addRow("芯片系列 (Family):", self.family_edit)

        self.package_edit = QLineEdit()
        self.package_edit.setPlaceholderText("例: LFBGA180, LQFP176, BGA516")
        form.addRow("封装规格 (Package):", self.package_edit)

        # CPU core specs
        self.core_count_spin = QSpinBox()
        self.core_count_spin.setRange(1, 16)
        self.core_count_spin.setValue(2)
        self.core_count_spin.valueChanged.connect(self._update_core_defaults)
        form.addRow("CPU 核数 (Core Count):", self.core_count_spin)

        self.avail_cores_edit = QLineEdit("CORE0, CORE1")
        form.addRow("可用核心列表 (Cores):", self.avail_cores_edit)

        self.master_core_edit = QLineEdit("CORE0")
        form.addRow("主核 (Master Core):", self.master_core_edit)

        self.desc_edit = QTextEdit()
        self.desc_edit.setMaximumHeight(80)
        self.desc_edit.setPlaceholderText("可选描述，例如: Entry level automotive MCU")
        form.addRow("描述 (Description):", self.desc_edit)

        layout.addWidget(form_group)
        layout.addStretch()
        self.tabs.addTab(tab, "1. 基础信息 (Basic Info)")

    def _setup_peripherals_tab(self):
        """Tab 2: Peripheral Capacities"""
        tab = QWidget()
        layout = QVBoxLayout(tab)
        layout.setContentsMargins(14, 14, 14, 14)

        # CAN
        can_group = QGroupBox("CAN 控制器配置 (CAN Controllers)")
        can_layout = QVBoxLayout(can_group)
        can_top = QHBoxLayout()
        can_top.addWidget(QLabel("控制器数量:"))
        self.can_count_spin = QSpinBox()
        self.can_count_spin.setRange(0, 16)
        self.can_count_spin.setValue(2)
        self.can_count_spin.valueChanged.connect(self._on_can_count_changed)
        can_top.addWidget(self.can_count_spin)

        self.can_fd_check = QCheckBox("支持 CAN-FD (Support CAN-FD)")
        can_top.addWidget(self.can_fd_check)
        can_top.addStretch()
        can_layout.addLayout(can_top)

        self.can_table = QTableWidget(0, 4)
        self.can_table.setHorizontalHeaderLabels(["控制器 ID", "名称", "最大波特率 (bps)", "邮箱数 (Mailboxes)"])
        self.can_table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.can_table.setMaximumHeight(140)
        can_layout.addWidget(self.can_table)
        layout.addWidget(can_group)

        # ADC
        adc_group = QGroupBox("ADC 转换器配置 (ADC Units)")
        adc_layout = QVBoxLayout(adc_group)
        adc_top = QHBoxLayout()
        adc_top.addWidget(QLabel("ADC 单元数量:"))
        self.adc_count_spin = QSpinBox()
        self.adc_count_spin.setRange(0, 16)
        self.adc_count_spin.setValue(4)
        self.adc_count_spin.valueChanged.connect(self._on_adc_count_changed)
        adc_top.addWidget(self.adc_count_spin)

        adc_top.addWidget(QLabel("分辨率 (bits):"))
        self.adc_res_combo = QComboBox()
        self.adc_res_combo.addItems(["12", "10", "14", "16"])
        adc_top.addWidget(self.adc_res_combo)
        adc_top.addStretch()
        adc_layout.addLayout(adc_top)

        self.adc_table = QTableWidget(0, 4)
        self.adc_table.setHorizontalHeaderLabels(["单元 ID", "单元名称", "通道数量", "通道列表 (0..N)"])
        self.adc_table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.adc_table.setMaximumHeight(140)
        adc_layout.addWidget(self.adc_table)
        layout.addWidget(adc_group)

        # SPI
        spi_group = QGroupBox("SPI 控制器配置 (SPI Units)")
        spi_top = QHBoxLayout(spi_group)
        spi_top.addWidget(QLabel("SPI 硬件模块数量:"))
        self.spi_count_spin = QSpinBox()
        self.spi_count_spin.setRange(0, 32)
        self.spi_count_spin.setValue(6)
        spi_top.addWidget(self.spi_count_spin)

        spi_top.addWidget(QLabel("最大时钟 (Hz):"))
        self.spi_baud_edit = QLineEdit("10000000")
        spi_top.addWidget(self.spi_baud_edit)

        self.spi_dma_check = QCheckBox("支持 DMA (Support DMA)")
        self.spi_dma_check.setChecked(True)
        spi_top.addWidget(self.spi_dma_check)
        spi_top.addStretch()
        layout.addWidget(spi_group)

        layout.addStretch()
        self.tabs.addTab(tab, "2. 外设规格 (Peripherals)")

        self._on_can_count_changed(self.can_count_spin.value())
        self._on_adc_count_changed(self.adc_count_spin.value())

    def _setup_pinout_tab(self):
        """Tab 3: Pinout & Multiplexing Matrix"""
        tab = QWidget()
        layout = QVBoxLayout(tab)
        layout.setContentsMargins(12, 12, 12, 12)

        # Action toolbar
        toolbar = QHBoxLayout()
        import_btn = QPushButton("📂 从 Excel / CSV 导入引脚表 (Import...)")
        import_btn.setStyleSheet("font-weight: bold; background-color: #2b579a; color: white; padding: 5px 12px;")
        import_btn.clicked.connect(self._on_import_pinout_clicked)
        toolbar.addWidget(import_btn)

        add_pin_btn = QPushButton("➕ 添加引脚 (Add Pin)")
        add_pin_btn.clicked.connect(self._on_add_pin_clicked)
        toolbar.addWidget(add_pin_btn)

        del_pin_btn = QPushButton("➖ 删除选中 (Delete)")
        del_pin_btn.clicked.connect(self._on_delete_pin_clicked)
        toolbar.addWidget(del_pin_btn)

        toolbar.addSpacing(15)
        toolbar.addWidget(QLabel("端口过滤:"))
        self.port_filter_combo = QComboBox()
        self.port_filter_combo.addItem("全部端口 (All Ports)")
        self.port_filter_combo.currentTextChanged.connect(self._filter_pin_table)
        toolbar.addWidget(self.port_filter_combo)

        toolbar.addStretch()
        self.pin_stats_label = QLabel("共 0 个端口，0 个引脚")
        toolbar.addWidget(self.pin_stats_label)

        layout.addLayout(toolbar)

        # Pin table
        self.pin_table = QTableWidget(0, 5)
        self.pin_table.setHorizontalHeaderLabels([
            "端口 (Port)", "引脚号 (Pin)", "引脚名称 (Name)", "默认方向 (Direction)", "复用功能清单 (Alternate Functions, 逗号分隔)"
        ])
        header = self.pin_table.horizontalHeader()
        header.setSectionResizeMode(0, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(1, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(2, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(3, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(4, QHeaderView.Stretch)
        self.pin_table.setSelectionBehavior(QAbstractItemView.SelectRows)

        layout.addWidget(self.pin_table, 1)
        self.tabs.addTab(tab, "3. 引脚复用矩阵 (Pinout & Mux)")

    def _setup_preview_tab(self):
        """Tab 4: Preview & Export"""
        tab = QWidget()
        layout = QVBoxLayout(tab)
        layout.setContentsMargins(12, 12, 12, 12)

        splitter = QSplitter(Qt.Horizontal)

        # Left: YAML
        yaml_box = QGroupBox("YAML 芯片模型定义 (data/chips/*.yaml)")
        yaml_layout = QVBoxLayout(yaml_box)
        self.yaml_preview = QTextEdit()
        self.yaml_preview.setFont(QFont("Menlo, Monaco, Consolas, Courier New", 10))
        self.yaml_preview.setReadOnly(True)
        yaml_layout.addWidget(self.yaml_preview)

        yaml_copy_btn = QPushButton("📋 复制 YAML (Copy)")
        yaml_copy_btn.clicked.connect(lambda: self._copy_to_clipboard(self.yaml_preview.toPlainText()))
        yaml_layout.addWidget(yaml_copy_btn)
        splitter.addWidget(yaml_box)

        # Right: .properties
        prop_box = QGroupBox("EB Tresos 资源属性文件 (*.properties)")
        prop_layout = QVBoxLayout(prop_box)
        self.prop_preview = QTextEdit()
        self.prop_preview.setFont(QFont("Menlo, Monaco, Consolas, Courier New", 10))
        self.prop_preview.setReadOnly(True)
        prop_layout.addWidget(self.prop_preview)

        prop_export_btn = QPushButton("📄 导出 .properties 文件... (Export)")
        prop_export_btn.clicked.connect(self._on_export_properties_clicked)
        prop_layout.addWidget(prop_export_btn)
        splitter.addWidget(prop_box)

        splitter.setSizes([450, 450])
        layout.addWidget(splitter, 1)

        self.tabs.addTab(tab, "4. 预览与导出 (Preview & Export)")

    def _populate_clone_dropdown(self):
        """Populate the clone combo box with existing chips from database"""
        self.clone_combo.clear()
        self.clone_combo.addItem("-- 选择要克隆的芯片模版 --", None)
        chips = self.chip_database.list_chips()
        for chip_name in sorted(chips):
            self.clone_combo.addItem(chip_name, chip_name)

    def _on_clone_clicked(self):
        """Clone selected chip into the designer"""
        chip_name = self.clone_combo.currentData()
        if not chip_name:
            QMessageBox.information(self, "提示", "请先从下拉菜单中选择一个要克隆的芯片型号。")
            return

        self._load_chip_by_name(chip_name)
        self.name_edit.setText(f"{chip_name}_COPY")
        self.status_label.setText(f"已克隆芯片模板: {chip_name}")
        QMessageBox.information(self, "克隆成功", f"已成功载入 {chip_name} 的全部规格与引脚定义，您可以直接在此基础上修改。")

    def _load_chip_by_name(self, chip_name: str):
        """Load chip by name into editor"""
        chip = self.chip_database.get_chip(chip_name)
        if not chip:
            return

        self.name_edit.setText(chip.name)
        self.family_edit.setText(chip.family)
        self.package_edit.setText(chip.package)
        self.desc_edit.setText(chip.description)

        # Peripherals
        if chip.can_resources:
            self.can_count_spin.setValue(len(chip.can_resources))
            self.can_fd_check.setChecked(any(c.supports_fd for c in chip.can_resources))
            for row, can in enumerate(chip.can_resources):
                if row < self.can_table.rowCount():
                    self.can_table.setItem(row, 0, QTableWidgetItem(str(can.controller_id)))
                    self.can_table.setItem(row, 1, QTableWidgetItem(can.name))
                    self.can_table.setItem(row, 2, QTableWidgetItem(str(can.max_baudrate)))
                    self.can_table.setItem(row, 3, QTableWidgetItem(str(can.mailbox_count)))

        if chip.adc_resources:
            self.adc_count_spin.setValue(len(chip.adc_resources))
            for row, adc in enumerate(chip.adc_resources):
                if row < self.adc_table.rowCount():
                    self.adc_table.setItem(row, 0, QTableWidgetItem(str(adc.unit_id)))
                    self.adc_table.setItem(row, 1, QTableWidgetItem(adc.name))
                    self.adc_table.setItem(row, 2, QTableWidgetItem(str(adc.channel_count)))
                    chs = ", ".join(str(c) for c in adc.channels)
                    self.adc_table.setItem(row, 3, QTableWidgetItem(chs))

        if chip.spi_resources:
            self.spi_count_spin.setValue(len(chip.spi_resources))

        # Ports
        self.current_ports = {
            port: [
                PortPinDef(
                    name=p.name,
                    port=p.port,
                    pin=p.pin,
                    alternate_functions=list(p.alternate_functions),
                    default_direction=p.default_direction
                )
                for p in pins
            ]
            for port, pins in chip.ports.items()
        }
        self._refresh_pin_table()

    def _init_default_fields(self):
        """Set up initial blank values"""
        self.name_edit.setText("NEW_MCU_SERIES")
        self.family_edit.setText("THA6")
        self.package_edit.setText("LQFP144")
        self.desc_edit.setText("Automotive MCU Resource Definition")

    def _update_core_defaults(self, count: int):
        """Update core lists when count changes"""
        cores = [f"CORE{i}" for i in range(count)]
        self.avail_cores_edit.setText(", ".join(cores))
        if self.master_core_edit.text() not in cores:
            self.master_core_edit.setText("CORE0")

    def _on_can_count_changed(self, count: int):
        """Update CAN controller table rows"""
        self.can_table.setRowCount(count)
        for i in range(count):
            if not self.can_table.item(i, 0):
                self.can_table.setItem(i, 0, QTableWidgetItem(str(i)))
                self.can_table.setItem(i, 1, QTableWidgetItem(f"CAN{i}"))
                self.can_table.setItem(i, 2, QTableWidgetItem("1000000"))
                self.can_table.setItem(i, 3, QTableWidgetItem("32"))

    def _on_adc_count_changed(self, count: int):
        """Update ADC controller table rows"""
        self.adc_table.setRowCount(count)
        for i in range(count):
            if not self.adc_table.item(i, 0):
                self.adc_table.setItem(i, 0, QTableWidgetItem(str(i)))
                self.adc_table.setItem(i, 1, QTableWidgetItem(f"SARADC{i}"))
                self.adc_table.setItem(i, 2, QTableWidgetItem("8"))
                self.adc_table.setItem(i, 3, QTableWidgetItem("0, 1, 2, 3, 4, 5, 6, 7"))

    def _on_import_pinout_clicked(self):
        """Launch file dialog to import pinout Excel/CSV"""
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "选择引脚分配表 (Select Pinout Table)",
            str(Path.home()),
            "Pinout Tables (*.xlsx *.csv *.xls);;Excel Files (*.xlsx *.xls);;CSV Files (*.csv);;All Files (*)"
        )
        if not file_path:
            return

        result = self.importer.import_file(Path(file_path))
        if not result.success:
            err_msg = "\n".join(result.errors[:5])
            QMessageBox.critical(self, "导入失败", f"无法解析引脚表:\n{err_msg}")
            return

        self.current_ports = result.ports
        self._refresh_pin_table()

        warn_info = f"\n警告: {len(result.warnings)} 条" if result.warnings else ""
        QMessageBox.information(
            self,
            "导入成功",
            f"成功导入 {result.total_pins} 个引脚，分布在 {len(result.ports)} 个端口中！{warn_info}"
        )
        self.status_label.setText(f"成功导入引脚表: {Path(file_path).name} ({result.total_pins} 个引脚)")

    def _refresh_pin_table(self):
        """Reload pinout table from in-memory current_ports"""
        # Update port filter combo
        current_filter = self.port_filter_combo.currentText()
        self.port_filter_combo.blockSignals(True)
        self.port_filter_combo.clear()
        self.port_filter_combo.addItem("全部端口 (All Ports)")
        for port_name in sorted(self.current_ports.keys()):
            self.port_filter_combo.addItem(port_name)

        idx = self.port_filter_combo.findText(current_filter)
        if idx != -1:
            self.port_filter_combo.setCurrentIndex(idx)
        else:
            self.port_filter_combo.setCurrentIndex(0)
        self.port_filter_combo.blockSignals(False)

        self._filter_pin_table(self.port_filter_combo.currentText())

    def _filter_pin_table(self, filter_port: str):
        """Filter and display rows in pin table"""
        self.pin_table.setRowCount(0)
        all_pins = []

        target_ports = sorted(self.current_ports.keys())
        if filter_port and filter_port != "全部端口 (All Ports)":
            target_ports = [filter_port] if filter_port in self.current_ports else []

        total_count = sum(len(pins) for pins in self.current_ports.values())
        self.pin_stats_label.setText(f"共 {len(self.current_ports)} 个端口，{total_count} 个引脚")

        for port_name in target_ports:
            for p in self.current_ports[port_name]:
                all_pins.append(p)

        self.pin_table.setRowCount(len(all_pins))
        for row, p in enumerate(all_pins):
            self.pin_table.setItem(row, 0, QTableWidgetItem(p.port))
            self.pin_table.setItem(row, 1, QTableWidgetItem(str(p.pin)))
            self.pin_table.setItem(row, 2, QTableWidgetItem(p.name))
            self.pin_table.setItem(row, 3, QTableWidgetItem(p.default_direction))
            self.pin_table.setItem(row, 4, QTableWidgetItem(", ".join(p.alternate_functions)))

    def _save_pin_table_edits(self):
        """Gather edits from pin_table back into current_ports"""
        for row in range(self.pin_table.rowCount()):
            port_item = self.pin_table.item(row, 0)
            pin_item = self.pin_table.item(row, 1)
            name_item = self.pin_table.item(row, 2)
            dir_item = self.pin_table.item(row, 3)
            af_item = self.pin_table.item(row, 4)

            if not port_item or not pin_item:
                continue

            port = port_item.text().strip()
            try:
                pin_id = int(pin_item.text().strip())
            except ValueError:
                continue

            name = name_item.text().strip() if name_item else f"{port}_{pin_id}"
            direction = dir_item.text().strip() if dir_item else "INPUT"
            raw_af = af_item.text().strip() if af_item else "GPIO"
            afs = [f.strip() for f in raw_af.split(",") if f.strip()]
            if not afs:
                afs = ["GPIO"]

            if port not in self.current_ports:
                self.current_ports[port] = []

            # Update existing or append
            found = False
            for p in self.current_ports[port]:
                if p.pin == pin_id:
                    p.name = name
                    p.default_direction = direction
                    p.alternate_functions = afs
                    found = True
                    break
            if not found:
                self.current_ports[port].append(PortPinDef(
                    name=name, port=port, pin=pin_id,
                    alternate_functions=afs, default_direction=direction
                ))

    def _on_add_pin_clicked(self):
        """Add a new pin row"""
        port = self.port_filter_combo.currentText()
        if not port or port == "全部端口 (All Ports)":
            port = "PORT_A"

        if port not in self.current_ports:
            self.current_ports[port] = []

        existing_pins = [p.pin for p in self.current_ports[port]]
        next_pin = max(existing_pins) + 1 if existing_pins else 0

        new_pin = PortPinDef(
            name=f"P{port.replace('PORT_', '')}{next_pin}",
            port=port,
            pin=next_pin,
            alternate_functions=["GPIO"],
            default_direction="INPUT"
        )
        self.current_ports[port].append(new_pin)
        self._refresh_pin_table()

    def _on_delete_pin_clicked(self):
        """Delete selected rows"""
        selected_rows = sorted(set(idx.row() for idx in self.pin_table.selectedIndexes()), reverse=True)
        if not selected_rows:
            return

        for row in selected_rows:
            port_item = self.pin_table.item(row, 0)
            pin_item = self.pin_table.item(row, 1)
            if port_item and pin_item:
                port = port_item.text().strip()
                try:
                    pin_id = int(pin_item.text().strip())
                    if port in self.current_ports:
                        self.current_ports[port] = [p for p in self.current_ports[port] if p.pin != pin_id]
                        if not self.current_ports[port]:
                            del self.current_ports[port]
                except ValueError:
                    pass

        self._refresh_pin_table()

    def _build_current_chip(self) -> ChipDefinition:
        """Construct ChipDefinition from all tabs"""
        self._save_pin_table_edits()

        name = self.name_edit.text().strip()
        family = self.family_edit.text().strip()
        package = self.package_edit.text().strip()
        desc = self.desc_edit.toPlainText().strip()

        chip = ChipDefinition(
            name=name or "UNNAMED_CHIP",
            family=family,
            package=package,
            description=desc,
        )

        # Ports
        chip.ports = self.current_ports

        # CAN
        can_res = []
        for r in range(self.can_table.rowCount()):
            cid_item = self.can_table.item(r, 0)
            cname_item = self.can_table.item(r, 1)
            cbaud_item = self.can_table.item(r, 2)
            cmail_item = self.can_table.item(r, 3)

            cid = int(cid_item.text()) if cid_item and cid_item.text().isdigit() else r
            cname = cname_item.text() if cname_item else f"CAN{cid}"
            cbaud = int(cbaud_item.text()) if cbaud_item and cbaud_item.text().isdigit() else 1000000
            cmail = int(cmail_item.text()) if cmail_item and cmail_item.text().isdigit() else 32

            can_res.append(CanResourceDef(
                name=cname,
                controller_id=cid,
                max_baudrate=cbaud,
                supports_fd=self.can_fd_check.isChecked(),
                mailbox_count=cmail
            ))
        chip.can_resources = can_res

        # ADC
        adc_res = []
        for r in range(self.adc_table.rowCount()):
            aid_item = self.adc_table.item(r, 0)
            aname_item = self.adc_table.item(r, 1)
            acnt_item = self.adc_table.item(r, 2)
            achs_item = self.adc_table.item(r, 3)

            aid = int(aid_item.text()) if aid_item and aid_item.text().isdigit() else r
            aname = aname_item.text() if aname_item else f"SARADC{aid}"
            acnt = int(acnt_item.text()) if acnt_item and acnt_item.text().isdigit() else 8

            channels = []
            if achs_item and achs_item.text():
                for c in achs_item.text().split(","):
                    c_clean = c.strip()
                    if c_clean.isdigit():
                        channels.append(int(c_clean))
            if not channels:
                channels = list(range(acnt))

            res_bits = int(self.adc_res_combo.currentText()) if self.adc_res_combo.currentText().isdigit() else 12

            adc_res.append(AdcResourceDef(
                name=aname,
                unit_id=aid,
                channel_count=acnt,
                resolution_bits=res_bits,
                channels=channels
            ))
        chip.adc_resources = adc_res

        # SPI
        spi_res = []
        spi_cnt = self.spi_count_spin.value()
        spi_baud = int(self.spi_baud_edit.text()) if self.spi_baud_edit.text().isdigit() else 10000000
        for i in range(spi_cnt):
            spi_res.append(SpiResourceDef(
                name=f"SPI{i}",
                unit_id=i,
                max_baudrate=spi_baud,
                supports_dma=self.spi_dma_check.isChecked()
            ))
        chip.spi_resources = spi_res

        return chip

    def _on_tab_changed(self, index: int):
        """Update preview when tab 4 is selected"""
        if index == 3:  # Preview tab
            chip = self._build_current_chip()
            yaml_str = self.exporter.to_yaml_string(chip)
            self.yaml_preview.setPlainText(yaml_str)

            num_cores = self.core_count_spin.value()
            avail_cores = [c.strip() for c in self.avail_cores_edit.text().split(",") if c.strip()]
            master_core = self.master_core_edit.text().strip() or "CORE0"
            prop_str = self.exporter.to_properties_string(
                chip, num_cores=num_cores, available_cores=avail_cores, master_core=master_core
            )
            self.prop_preview.setPlainText(prop_str)

    def _copy_to_clipboard(self, text: str):
        """Copy string to system clipboard"""
        QGuiApplication.clipboard().setText(text)
        self.status_label.setText("已复制到剪贴板！")

    def _on_export_properties_clicked(self):
        """Export .properties file via file dialog"""
        chip = self._build_current_chip()
        default_filename = f"CotexR52_{chip.name}.properties"
        file_path, _ = QFileDialog.getSaveFileName(
            self,
            "导出 EB Tresos 属性文件",
            default_filename,
            "Properties Files (*.properties);;All Files (*)"
        )
        if not file_path:
            return

        num_cores = self.core_count_spin.value()
        avail_cores = [c.strip() for c in self.avail_cores_edit.text().split(",") if c.strip()]
        master_core = self.master_core_edit.text().strip() or "CORE0"

        try:
            self.exporter.save_properties(
                chip, Path(file_path),
                num_cores=num_cores, available_cores=avail_cores, master_core=master_core
            )
            QMessageBox.information(self, "导出成功", f"成功导出属性文件:\n{file_path}")
            self.status_label.setText(f"已导出属性文件: {Path(file_path).name}")
        except Exception as e:
            QMessageBox.critical(self, "导出错误", f"导出失败:\n{str(e)}")

    def _on_save_clicked(self):
        """Save the chip definition to data/chips/<name>.yaml and notify system"""
        chip = self._build_current_chip()
        if not chip.name or chip.name == "UNNAMED_CHIP":
            QMessageBox.warning(self, "验证失败", "请输入有效的芯片型号名称！")
            self.tabs.setCurrentIndex(0)
            self.name_edit.setFocus()
            return

        if not chip.ports:
            reply = QMessageBox.question(
                self,
                "引脚表为空",
                "当前芯片尚未定义任何端口与引脚，确定要保存吗？",
                QMessageBox.Yes | QMessageBox.No,
                QMessageBox.No
            )
            if reply != QMessageBox.Yes:
                self.tabs.setCurrentIndex(2)
                return

        target_file = self._get_default_data_dir() / f"{chip.name}.yaml"
        try:
            self.exporter.save_yaml(chip, target_file)

            # Register in database
            self._last_saved_chip = chip.name
            self.chip_database._chips[chip.name] = chip
            self._populate_clone_dropdown()

            self.status_label.setText(f"✅ 已成功保存芯片: {chip.name}")
            self.status_label.setStyleSheet("color: #4caf50; font-weight: bold; font-size: 12px;")
            self.chip_saved.emit(chip.name)

            QMessageBox.information(
                self,
                "保存成功",
                f"芯片定义已成功保存到系统数据库！\n\n文件路径: {target_file}\n"
                f"在后续的硬件映射向导和配置面板中，可以直接选择此芯片。\n\n"
                f"您可以继续编辑或导出 .properties 文件，也可以直接关闭。"
            )
        except Exception as e:
            QMessageBox.critical(self, "保存错误", f"保存芯片定义失败:\n{str(e)}")

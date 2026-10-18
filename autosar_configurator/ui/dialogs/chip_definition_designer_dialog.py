"""
Chip Definition Designer Dialog

A graphical interface for semiconductor chip engineers and ECU integrators
to author, edit, clone, validate, and export MCU chip hardware definitions.
"""
import copy
import re
from collections import Counter
from pathlib import Path
from typing import Dict, List, Optional, Set, Tuple
import logging

from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QFormLayout, QLineEdit,
    QTextEdit, QLabel, QGroupBox, QWidget, QComboBox, QPushButton,
    QSpinBox, QTabWidget, QTableWidget, QTableWidgetItem,
    QHeaderView, QMessageBox, QFileDialog, QSplitter, QAbstractItemView,
    QTableView
)
from PySide6.QtCore import (
    Qt, Signal, QAbstractTableModel, QModelIndex, QSortFilterProxyModel,
    QRegularExpression
)
from PySide6.QtGui import QFont, QGuiApplication, QBrush, QColor

from ...core.hardware.chip_database import (
    ChipDatabase, ChipDefinition, PortPinDef
)
from ...core.hardware.pinout_importer import PinoutTableImporter
from ...core.hardware.chip_exporter import ChipDefinitionExporter
from ...core.hardware.ecu_resource_data import (
    EcuResources, count_placeholders, describe_ecu_resources, flatten_ecu_resources,
)
from ...core.hardware.ecu_resource_data import parse_selectors
from ...core.hardware.ecu_resource_diagnostics import (
    check_consistency, typed_field_differences, typed_fields_from_ecu,
)
from .ecu_resource_editor import EcuResourceEditor
from .peripheral_editor import PeripheralEditor
from ...core.hardware.mapping_rule import rule_resource_requirements

logger = logging.getLogger(__name__)

# Shown above the .properties preview of a chip that has no ECU resources
FALLBACK_NOTE = (
    "# 兜底推导，非权威数据: 本芯片没有 ECU 资源 (ecu_resources)，下列值由设计器字段推导或写死，\n"
    "# 可能与真实芯片不符。请在 \"4. ECU 资源\" 页导入或填写后再导出。\n"
)

ALL_PORTS_LABEL = "全部端口 (All Ports)"
VALID_DIRECTIONS = ("INPUT", "OUTPUT", "INOUT")
# Chip name doubles as the YAML file name: no path separators or leading dots.
CHIP_NAME_PATTERN = re.compile(r'^[A-Za-z0-9][A-Za-z0-9_.\-]*$')
_MODE_TOKEN = re.compile(r'^(\d+)\s*[:=]\s*(.+)$')


def format_pin_functions(pin: PortPinDef) -> str:
    """Render functions for editing: '0:GPIO, 2:CAN0_TX' when mode numbers are known"""
    if pin.alt_modes:
        return ", ".join(f"{m}:{pin.alt_modes[m]}" for m in sorted(pin.alt_modes))
    return ", ".join(pin.alternate_functions)


def parse_pin_functions(text: str) -> Tuple[List[str], Dict[int, str]]:
    """Inverse of format_pin_functions -> (flat function list, mode number map)"""
    afs: List[str] = []
    modes: Dict[int, str] = {}
    for token in (t.strip() for t in text.split(",")):
        if not token:
            continue
        m = _MODE_TOKEN.match(token)
        if m:
            value = m.group(2).strip()
            modes[int(m.group(1))] = value
            names = [n.strip() for n in value.split("/") if n.strip()]
        else:
            names = [token]
        for name in names:
            if name not in afs:
                afs.append(name)
    return afs or ["GPIO"], modes


class PinTableModel(QAbstractTableModel):
    """Editable model over a flat list of PortPinDef; edits apply to the pins directly"""

    COL_PORT, COL_PIN, COL_NAME, COL_DIR, COL_FUNCS = range(5)
    HEADERS = [
        "端口 (Port)", "引脚号 (Pin)", "引脚名称 (Name)", "默认方向 (Direction)",
        "复用功能 (Functions, 逗号分隔; 模式号写作 2:CAN0_TX)"
    ]

    def __init__(self, parent=None):
        super().__init__(parent)
        self._pins: List[PortPinDef] = []
        self._duplicates: Set[Tuple[str, int]] = set()

    # --- Qt model API -------------------------------------------------
    def rowCount(self, parent=QModelIndex()):
        return 0 if parent.isValid() else len(self._pins)

    def columnCount(self, parent=QModelIndex()):
        return 0 if parent.isValid() else len(self.HEADERS)

    def headerData(self, section, orientation, role=Qt.DisplayRole):
        if role == Qt.DisplayRole and orientation == Qt.Horizontal:
            return self.HEADERS[section]
        return None

    def flags(self, index):
        if not index.isValid():
            return Qt.NoItemFlags
        return Qt.ItemIsSelectable | Qt.ItemIsEnabled | Qt.ItemIsEditable

    def data(self, index, role=Qt.DisplayRole):
        if not index.isValid():
            return None
        pin = self._pins[index.row()]
        col = index.column()
        if role in (Qt.DisplayRole, Qt.EditRole):
            if col == self.COL_PORT:
                return pin.port
            if col == self.COL_PIN:
                return pin.pin if role == Qt.EditRole else str(pin.pin)
            if col == self.COL_NAME:
                return pin.name
            if col == self.COL_DIR:
                return pin.default_direction
            if col == self.COL_FUNCS:
                return format_pin_functions(pin)
        if role == Qt.BackgroundRole and (pin.port, pin.pin) in self._duplicates:
            return QBrush(QColor("#f8d7da"))
        if role == Qt.ToolTipRole and (pin.port, pin.pin) in self._duplicates:
            return f"重复引脚: {pin.port} / {pin.pin}"
        return None

    def setData(self, index, value, role=Qt.EditRole):
        if role != Qt.EditRole or not index.isValid():
            return False
        pin = self._pins[index.row()]
        col = index.column()
        text = str(value).strip()
        if col == self.COL_PORT:
            if not text:
                return False
            pin.port = text
        elif col == self.COL_PIN:
            try:
                pin_id = int(text)
            except ValueError:
                return False
            if pin_id < 0:
                return False
            pin.pin = pin_id
        elif col == self.COL_NAME:
            if not text:
                return False
            pin.name = text
        elif col == self.COL_DIR:
            direction = text.upper()
            if direction not in VALID_DIRECTIONS:
                return False
            pin.default_direction = direction
        elif col == self.COL_FUNCS:
            pin.alternate_functions, pin.alt_modes = parse_pin_functions(text)
        else:
            return False
        self.dataChanged.emit(index, index, [role])
        if col in (self.COL_PORT, self.COL_PIN):
            self._update_duplicates()
        return True

    # --- Convenience API ----------------------------------------------
    def set_pins(self, pins: List[PortPinDef]):
        self.beginResetModel()
        self._pins = sorted(copy.deepcopy(pins), key=lambda p: (p.port, p.pin))
        self.endResetModel()
        self._update_duplicates()

    def add_pin(self, pin: PortPinDef) -> int:
        row = len(self._pins)
        self.beginInsertRows(QModelIndex(), row, row)
        self._pins.append(pin)
        self.endInsertRows()
        self._update_duplicates()
        return row

    def remove_rows(self, rows: List[int]):
        valid_rows = sorted({r for r in rows if 0 <= r < len(self._pins)}, reverse=True)
        if not valid_rows:
            return
        if len(valid_rows) > 1:
            self.beginResetModel()
            for row in valid_rows:
                del self._pins[row]
            self.endResetModel()
        else:
            row = valid_rows[0]
            self.beginRemoveRows(QModelIndex(), row, row)
            del self._pins[row]
            self.endRemoveRows()
        self._update_duplicates()

    def pins(self) -> List[PortPinDef]:
        return self._pins

    def ports_dict(self) -> Dict[str, List[PortPinDef]]:
        """Pins grouped by port, sorted by port then pin (deterministic output)"""
        result: Dict[str, List[PortPinDef]] = {}
        for p in sorted(self._pins, key=lambda x: (x.port, x.pin)):
            result.setdefault(p.port, []).append(p)
        return result

    def duplicates(self) -> Set[Tuple[str, int]]:
        return set(self._duplicates)

    def _update_duplicates(self):
        counts = Counter((p.port, p.pin) for p in self._pins)
        new_dups = {k for k, n in counts.items() if n > 1}
        if new_dups != self._duplicates:
            self._duplicates = new_dups
            if self._pins:
                self.dataChanged.emit(
                    self.index(0, 0), self.index(len(self._pins) - 1, self.columnCount() - 1),
                    [Qt.BackgroundRole, Qt.ToolTipRole]
                )


class ChipDefinitionDesignerDialog(QDialog):
    """Graphical designer for MCU chip hardware resource definitions"""

    chip_saved = Signal(str)  # Emits chip_name when successfully saved

    def __init__(self, chip_database: Optional[ChipDatabase] = None, initial_chip: Optional[str] = None,
                 parent=None, project=None):
        super().__init__(parent)
        # Project the designer was opened from (None when opened on its own): the
        # needed-keys guide can scan the modules loaded in it
        self._project = project
        self.chip_database = chip_database or ChipDatabase(self._get_default_data_dir())
        self.exporter = ChipDefinitionExporter()
        self.importer = PinoutTableImporter()

        # Chip the editor was loaded from: carries data the UI does not edit
        # (intc_sources, metadata) so a save never silently drops it.
        self._base_chip: Optional[ChipDefinition] = None
        # Name of the chip whose file is being edited (None for new / cloned chips)
        self._editing_name: Optional[str] = None
        self._last_saved_chip: Optional[str] = None
        # ECU resources (ecu:get/ecu:list data) and their version: not edited
        # field by field; filled by "Import properties" or loaded with the chip.
        self._ecu_resources: EcuResources = {}
        self._resource_version: str = ""

        self.setWindowTitle("Chip Definition Designer - 芯片定义设计器")
        self.resize(920, 700)
        self.setMinimumWidth(800)
        self.setMinimumHeight(600)

        self._setup_ui()
        self._populate_clone_dropdown()

        if not (initial_chip and self._load_chip_by_name(initial_chip)):
            self._init_default_fields()

    @property
    def current_ports(self) -> Dict[str, List[PortPinDef]]:
        """Current pins grouped by port (live objects from the pin model)"""
        return self.pin_model.ports_dict()

    def _get_default_data_dir(self) -> Path:
        """Default data/chips directory inside the package"""
        pkg_dir = Path(__file__).resolve().parent.parent.parent
        return pkg_dir / "data" / "chips"

    def _get_save_dir(self) -> Path:
        """Save next to the database's own files so a reload finds the chip"""
        return self.chip_database.data_dir or self._get_default_data_dir()

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

        self._setup_basic_tab()
        self._setup_peripherals_tab()
        self._setup_pinout_tab()
        self._setup_ecu_tab()
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
        self.name_edit.setPlaceholderText("例: THA610X_LFBGA180 (字母/数字/_ . -)")
        form.addRow("芯片型号 (Name)*:", self.name_edit)

        self.family_edit = QLineEdit()
        self.family_edit.setPlaceholderText("例: THA6")
        form.addRow("芯片系列 (Family):", self.family_edit)

        self.package_edit = QLineEdit()
        self.package_edit.setPlaceholderText("例: LFBGA180, LQFP176, BGA516")
        form.addRow("封装规格 (Package):", self.package_edit)

        # CPU core specs (persisted under metadata['cores'])
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

        # Where the typed core fields disagree with the ECU resources (which prevail)
        diff_row = QHBoxLayout()
        self.typed_diff_label = QLabel()
        self.typed_diff_label.setWordWrap(True)
        self.typed_diff_label.setStyleSheet("color: #8a4b00;")
        diff_row.addWidget(self.typed_diff_label, 1)
        self.typed_diff_btn = QPushButton("用 ECU 资源覆盖表单")
        self.typed_diff_btn.setToolTip("ECU 资源是模板实际读取的数据；把核数、可用核、主核改成 ECU 资源里的值")
        self.typed_diff_btn.clicked.connect(self._overwrite_typed_fields_from_ecu)
        diff_row.addWidget(self.typed_diff_btn)
        layout.addLayout(diff_row)

        # Chip selectors: value of each module's selector parameter for this chip
        sel_group = QGroupBox("芯片选择器 (Selectors)：本芯片在各模块选择器参数上的取值")
        sel_layout = QVBoxLayout(sel_group)
        sel_hint = QLabel("例：Resource.ResourceSubderivative → THA6412_BGA516；"
                          "Os.OsResourceSubderivative → Os_THA6412。新芯片无需修改模块定义文件即可被选择。")
        sel_hint.setWordWrap(True)
        sel_layout.addWidget(sel_hint)
        self.selectors_table = QTableWidget(0, 2)
        self.selectors_table.setHorizontalHeaderLabels(["模块.参数 (Module.Parameter)", "取值 (Value)"])
        self.selectors_table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.selectors_table.setMaximumHeight(130)
        sel_layout.addWidget(self.selectors_table)
        sel_buttons = QHBoxLayout()
        add_sel = QPushButton("增加一行")
        add_sel.clicked.connect(lambda: self.selectors_table.insertRow(self.selectors_table.rowCount()))
        sel_buttons.addWidget(add_sel)
        del_sel = QPushButton("删除所选行")
        del_sel.clicked.connect(self._remove_selector_rows)
        sel_buttons.addWidget(del_sel)
        sel_buttons.addStretch()
        sel_layout.addLayout(sel_buttons)
        layout.addWidget(sel_group)

        layout.addStretch()
        self.tabs.addTab(tab, "1. 基础信息 (Basic Info)")

    # --- selectors ------------------------------------------------------------

    def _set_selectors(self, selectors: Dict[str, str]):
        self.selectors_table.setRowCount(0)
        for key in sorted(selectors):
            row = self.selectors_table.rowCount()
            self.selectors_table.insertRow(row)
            self.selectors_table.setItem(row, 0, QTableWidgetItem(key))
            self.selectors_table.setItem(row, 1, QTableWidgetItem(selectors[key]))

    def _remove_selector_rows(self):
        for row in sorted({i.row() for i in self.selectors_table.selectedItems()}, reverse=True):
            self.selectors_table.removeRow(row)

    def _selectors_from_table(self) -> Dict[str, str]:
        """The selectors entered in the table; raises ValueError naming a bad row."""
        raw = {}
        for row in range(self.selectors_table.rowCount()):
            key_item, value_item = self.selectors_table.item(row, 0), self.selectors_table.item(row, 1)
            key = key_item.text().strip() if key_item else ""
            value = value_item.text().strip() if value_item else ""
            if not key and not value:
                continue
            if key in raw:
                raise ValueError(f"selectors: '{key}' appears twice")
            raw[key] = value
        return parse_selectors(raw)

    # --- typed fields vs ECU resources ------------------------------------------

    def _refresh_typed_differences(self):
        if not hasattr(self, "pin_model") or not hasattr(self, "ecu_editor"):
            return []       # tab change signals fire while the tabs are still being built
        messages = typed_field_differences(self._build_current_chip())
        self.typed_diff_label.setText("\n".join(messages))
        self.typed_diff_btn.setEnabled(bool(messages))
        return messages

    def _overwrite_typed_fields_from_ecu(self):
        values = typed_fields_from_ecu(self._build_current_chip())
        if "count" in values and isinstance(values["count"], int):
            self.core_count_spin.blockSignals(True)
            self.core_count_spin.setValue(values["count"])
            self.core_count_spin.blockSignals(False)
        if "available" in values:
            self.avail_cores_edit.setText(", ".join(values["available"]))
        if "master" in values:
            self.master_core_edit.setText(values["master"])
        self._refresh_typed_differences()

    def _setup_peripherals_tab(self):
        """Tab 2: peripheral instances of any type (chip YAML "resources")"""
        self.peripheral_editor = PeripheralEditor(requirements=rule_resource_requirements())
        self.tabs.addTab(self.peripheral_editor, "2. 外设 (Peripherals)")

    def _setup_pinout_tab(self):
        """Tab 3: Pinout & Multiplexing Matrix"""
        tab = QWidget()
        layout = QVBoxLayout(tab)
        layout.setContentsMargins(12, 12, 12, 12)

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
        self.port_filter_combo.addItem(ALL_PORTS_LABEL)
        self.port_filter_combo.currentTextChanged.connect(self._filter_pin_table)
        toolbar.addWidget(self.port_filter_combo)

        toolbar.addStretch()
        self.pin_stats_label = QLabel("共 0 个端口，0 个引脚")
        toolbar.addWidget(self.pin_stats_label)

        layout.addLayout(toolbar)

        # Model/View: edits go straight into the model, so filtering,
        # adding or deleting rows can never discard pending changes.
        self.pin_model = PinTableModel(self)
        self.pin_proxy = QSortFilterProxyModel(self)
        self.pin_proxy.setSourceModel(self.pin_model)
        self.pin_proxy.setFilterKeyColumn(PinTableModel.COL_PORT)

        self.pin_table = QTableView()
        self.pin_table.setModel(self.pin_proxy)
        header = self.pin_table.horizontalHeader()
        for col in range(PinTableModel.COL_FUNCS):
            header.setSectionResizeMode(col, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(PinTableModel.COL_FUNCS, QHeaderView.Stretch)
        self.pin_table.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.pin_table.verticalHeader().setVisible(False)

        for sig in (self.pin_model.dataChanged, self.pin_model.modelReset,
                    self.pin_model.rowsInserted, self.pin_model.rowsRemoved):
            sig.connect(self._on_pin_model_changed)

        layout.addWidget(self.pin_table, 1)
        self.tabs.addTab(tab, "3. 引脚复用矩阵 (Pinout & Mux)")

    def _setup_ecu_tab(self):
        """Tab 4: ECU resources (every key of every module)"""
        self.ecu_editor = EcuResourceEditor()
        self.ecu_editor.set_context(self.chip_database, lambda: self.name_edit.text().strip(), self._project)
        self.ecu_editor.import_requested.connect(self._on_import_properties_clicked)
        self.ecu_editor.changed.connect(self._on_ecu_edited)
        self.tabs.addTab(self.ecu_editor, "4. ECU 资源 (ECU Resources)")

    def _on_ecu_edited(self):
        self._ecu_resources = self.ecu_editor.resources()
        self._refresh_typed_differences()

    def _set_ecu_resources(self, resources: EcuResources):
        """Replace the chip's ECU resources everywhere they are shown."""
        self._ecu_resources = resources
        self.ecu_editor.set_resources(resources)
        self.ecu_preview.setPlainText(describe_ecu_resources(resources))

    def _setup_preview_tab(self):
        """Tab 4: Preview & Export"""
        tab = QWidget()
        layout = QVBoxLayout(tab)
        layout.setContentsMargins(12, 12, 12, 12)

        splitter = QSplitter(Qt.Horizontal)

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

        ecu_box = QGroupBox("ECU 资源 (ecu_resources，只读预览；来自 YAML 或导入的 .properties)")
        ecu_layout = QVBoxLayout(ecu_box)
        self.ecu_preview = QTextEdit()
        self.ecu_preview.setFont(QFont("Menlo, Monaco, Consolas, Courier New", 10))
        self.ecu_preview.setReadOnly(True)
        self.ecu_preview.setPlaceholderText("尚无 ECU 资源。可通过下方按钮导入 .properties 文件。")
        self.ecu_preview.setMaximumHeight(170)
        ecu_layout.addWidget(self.ecu_preview)

        self.consistency_label = QLabel()
        self.consistency_label.setWordWrap(True)
        self.consistency_label.setStyleSheet("color: #8a4b00;")
        ecu_layout.addWidget(self.consistency_label)
        layout.addWidget(ecu_box)

        self.tabs.addTab(tab, "5. 预览与导出 (Preview & Export)")

    def _populate_clone_dropdown(self):
        """Populate the clone combo box with existing chips from database"""
        self.clone_combo.clear()
        self.clone_combo.addItem("-- 选择要克隆的芯片模版 --", None)
        for chip_name in sorted(self.chip_database.list_chips()):
            self.clone_combo.addItem(chip_name, chip_name)

    def _on_clone_clicked(self):
        """Clone selected chip into the designer"""
        chip_name = self.clone_combo.currentData()
        if not chip_name:
            QMessageBox.information(self, "提示", "请先从下拉菜单中选择一个要克隆的芯片型号。")
            return

        if not self._load_chip_by_name(chip_name):
            return
        # A clone is a new chip: saving must not silently overwrite the source
        self._editing_name = None
        self.name_edit.setText(f"{chip_name}_COPY")
        self.status_label.setText(f"已克隆芯片模板: {chip_name}")
        QMessageBox.information(self, "克隆成功", f"已成功载入 {chip_name} 的全部规格与引脚定义，您可以直接在此基础上修改。")

    def _load_chip_by_name(self, chip_name: str) -> bool:
        """Load chip by name into editor; every field is reset, nothing leaks from the previous chip"""
        chip = self.chip_database.get_chip(chip_name)
        if not chip:
            QMessageBox.warning(self, "未找到芯片", f"芯片库中不存在芯片: {chip_name}")
            return False

        self._base_chip = copy.deepcopy(chip)
        self._editing_name = chip.name
        self._set_ecu_resources(copy.deepcopy(chip.ecu_resources))
        self._resource_version = chip.resource_version
        self._set_selectors(chip.selectors)

        self.name_edit.setText(chip.name)
        self.family_edit.setText(chip.family)
        self.package_edit.setText(chip.package)
        self.desc_edit.setPlainText(chip.description)

        cores = chip.metadata.get('cores') if isinstance(chip.metadata.get('cores'), dict) else {}
        self.core_count_spin.blockSignals(True)
        self.core_count_spin.setValue(int(cores.get('count', 2)))
        self.core_count_spin.blockSignals(False)
        available = cores.get('available') or [f"CORE{i}" for i in range(self.core_count_spin.value())]
        self.avail_cores_edit.setText(", ".join(available))
        self.master_core_edit.setText(cores.get('master', "CORE0"))

        self.peripheral_editor.set_resources(copy.deepcopy(chip.effective_resources()))

        self.pin_model.set_pins(chip.get_all_pins())
        return True

    def _init_default_fields(self):
        """Set up initial blank values"""
        self._base_chip = None
        self._editing_name = None
        self._set_ecu_resources({})
        self._resource_version = ""
        self._set_selectors({})
        self.peripheral_editor.set_resources({})
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

    def _on_import_pinout_clicked(self):
        """Launch file dialog to import pinout Excel/CSV"""
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "选择引脚分配表 (Select Pinout Table)",
            str(Path.home()),
            "Pinout Tables (*.xlsx *.xlsm *.csv);;Excel Files (*.xlsx *.xlsm);;CSV Files (*.csv);;All Files (*)"
        )
        if not file_path:
            return
        self._import_pinout_file(Path(file_path))

    def _import_pinout_file(self, file_path: Path):
        result = self.importer.import_file(file_path)
        if not result.success:
            err_msg = "\n".join(result.errors[:5])
            QMessageBox.critical(self, "导入失败", f"无法解析引脚表:\n{err_msg}")
            return

        existing = len(self.pin_model.pins())
        if existing:
            reply = QMessageBox.question(
                self, "替换现有引脚",
                f"当前已有 {existing} 个引脚，导入将替换为表格中的 {result.total_pins} 个引脚。是否继续？",
                QMessageBox.Yes | QMessageBox.No, QMessageBox.No
            )
            if reply != QMessageBox.Yes:
                return

        self.pin_model.set_pins([p for pins in result.ports.values() for p in pins])

        warn_info = ""
        if result.warnings:
            shown = "\n".join(result.warnings[:10])
            more = f"\n... 另有 {len(result.warnings) - 10} 条" if len(result.warnings) > 10 else ""
            warn_info = f"\n\n警告 {len(result.warnings)} 条:\n{shown}{more}"
        QMessageBox.information(
            self,
            "导入成功",
            f"成功导入 {result.total_pins} 个引脚，分布在 {len(result.ports)} 个端口中！{warn_info}"
        )
        self.status_label.setText(f"成功导入引脚表: {file_path.name} ({result.total_pins} 个引脚)")

    def _on_pin_model_changed(self, *args):
        """Keep the port filter list and statistics in sync with the model"""
        ports = sorted({p.port for p in self.pin_model.pins()})
        current = self.port_filter_combo.currentText()
        self.port_filter_combo.blockSignals(True)
        self.port_filter_combo.clear()
        self.port_filter_combo.addItem(ALL_PORTS_LABEL)
        self.port_filter_combo.addItems(ports)
        idx = self.port_filter_combo.findText(current)
        self.port_filter_combo.setCurrentIndex(idx if idx != -1 else 0)
        self.port_filter_combo.blockSignals(False)
        self._filter_pin_table(self.port_filter_combo.currentText())

        total = len(self.pin_model.pins())
        dups = self.pin_model.duplicates()
        dup_info = f"，⚠ {len(dups)} 处重复" if dups else ""
        self.pin_stats_label.setText(f"共 {len(ports)} 个端口，{total} 个引脚{dup_info}")

    def _filter_pin_table(self, filter_port: str):
        """Show only pins of the selected port (exact match, PORT_1 != PORT_10)"""
        if not filter_port or filter_port == ALL_PORTS_LABEL:
            self.pin_proxy.setFilterRegularExpression(QRegularExpression())
        else:
            self.pin_proxy.setFilterRegularExpression(
                QRegularExpression(f"^{QRegularExpression.escape(filter_port)}$")
            )

    def _on_add_pin_clicked(self):
        """Add a new pin row"""
        port = self.port_filter_combo.currentText()
        if not port or port == ALL_PORTS_LABEL:
            existing_ports = sorted({p.port for p in self.pin_model.pins()})
            port = existing_ports[0] if existing_ports else "PORT_A"

        existing_pins = [p.pin for p in self.pin_model.pins() if p.port == port]
        next_pin = max(existing_pins) + 1 if existing_pins else 0

        row = self.pin_model.add_pin(PortPinDef(
            name=f"P{port.replace('PORT_', '')}{next_pin}",
            port=port,
            pin=next_pin,
            alternate_functions=["GPIO"],
            default_direction="INPUT"
        ))
        proxy_index = self.pin_proxy.mapFromSource(self.pin_model.index(row, PinTableModel.COL_NAME))
        if proxy_index.isValid():
            self.pin_table.setCurrentIndex(proxy_index)
            self.pin_table.scrollTo(proxy_index)

    def _on_delete_pin_clicked(self):
        """Delete selected rows"""
        rows = [
            self.pin_proxy.mapToSource(idx).row()
            for idx in self.pin_table.selectionModel().selectedRows()
        ]
        if rows:
            self.pin_model.remove_rows(rows)

    def _build_current_chip(self) -> ChipDefinition:
        """Construct a ChipDefinition (independent copy) from all tabs"""
        base = self._base_chip
        default_metadata = {
            'cpu_frequency': 80000000,
            'flash_size': '512KB',
            'ram_size': '64KB',
        }
        initial_metadata = copy.deepcopy(base.metadata) if base and base.metadata else default_metadata

        chip = ChipDefinition(
            name=self.name_edit.text().strip() or "UNNAMED_CHIP",
            family=self.family_edit.text().strip(),
            package=self.package_edit.text().strip(),
            description=self.desc_edit.toPlainText().strip(),
            ports=copy.deepcopy(self.pin_model.ports_dict()),
            resources=self.peripheral_editor.resources(),
            metadata=initial_metadata,
            ecu_resources=copy.deepcopy(self._ecu_resources),
            resource_version=self._resource_version,
        )
        try:
            chip.selectors = self._selectors_from_table()
        except ValueError:
            chip.selectors = {}

        avail_cores = [c.strip() for c in self.avail_cores_edit.text().split(",") if c.strip()]
        chip.metadata['cores'] = {
            'count': self.core_count_spin.value(),
            'available': avail_cores,
            'master': self.master_core_edit.text().strip() or "CORE0",
        }

        return chip

    def _on_tab_changed(self, index: int):
        """Update preview when tab 4 is selected"""
        if index == 4:  # Preview tab
            chip = self._build_current_chip()
            self.yaml_preview.setPlainText(self.exporter.to_yaml_string(chip))
            cores = chip.metadata['cores']
            text = self.exporter.to_properties_string(
                chip, num_cores=cores['count'], available_cores=cores['available'], master_core=cores['master']
            )
            if not chip.ecu_resources:
                text = FALLBACK_NOTE + text
            self.prop_preview.setPlainText(text)
            self.ecu_preview.setPlainText(describe_ecu_resources(chip.ecu_resources))
            self.consistency_label.setText("\n".join(
                check_consistency(flatten_ecu_resources(chip.ecu_resources))
                + typed_field_differences(chip)))
        elif index == 0:
            self._refresh_typed_differences()

    def _copy_to_clipboard(self, text: str):
        """Copy string to system clipboard"""
        QGuiApplication.clipboard().setText(text)
        self.status_label.setText("已复制到剪贴板！")

    def _on_import_properties_clicked(self):
        """Merge the keys of one or more .properties files into the chip's ECU resources"""
        file_paths, _ = QFileDialog.getOpenFileNames(
            self, "导入 EB Tresos 属性文件", str(Path.home()),
            "Properties Files (*.properties);;All Files (*)"
        )
        if not file_paths:
            return

        scratch = ChipDefinition(name=self.name_edit.text().strip() or "UNNAMED_CHIP",
                                 ecu_resources=copy.deepcopy(self._ecu_resources))
        try:
            count = self.chip_database.import_ecu_resources_from_properties(
                scratch, [Path(p) for p in file_paths])
        except Exception as e:
            logger.exception("Failed to import properties")
            QMessageBox.critical(self, "导入错误", f"无法解析属性文件:\n{str(e)}")
            return

        self._set_ecu_resources(scratch.ecu_resources)
        self.status_label.setText(f"已导入 {count} 个键（来自 {len(file_paths)} 个文件），保存芯片后写入 YAML")

    def _on_export_properties_clicked(self):
        """Export .properties file via file dialog"""
        chip = self._build_current_chip()
        if chip.ecu_resources:
            # One file per module, content only from the chip's ecu_resources
            target_dir = QFileDialog.getExistingDirectory(
                self, "选择导出目录（每个模块一个 .properties 文件）", str(Path.home()))
            if not target_dir:
                return
            try:
                written = self.exporter.save_module_properties(chip, Path(target_dir))
            except Exception as e:
                QMessageBox.critical(self, "导出错误", f"导出失败:\n{str(e)}")
                return
            QMessageBox.information(
                self, "导出成功",
                "成功导出属性文件:\n" + "\n".join(str(p) for p in written))
            self.status_label.setText(f"已导出 {len(written)} 个属性文件")
            return
        file_path, _ = QFileDialog.getSaveFileName(
            self,
            "导出 EB Tresos 属性文件",
            f"CotexR52_{chip.name}.properties",
            "Properties Files (*.properties);;All Files (*)"
        )
        if not file_path:
            return

        cores = chip.metadata['cores']
        try:
            self.exporter.save_properties(
                chip, Path(file_path),
                num_cores=cores['count'], available_cores=cores['available'], master_core=cores['master']
            )
            QMessageBox.information(self, "导出成功", f"成功导出属性文件:\n{file_path}")
            self.status_label.setText(f"已导出属性文件: {Path(file_path).name}")
        except Exception as e:
            QMessageBox.critical(self, "导出错误", f"导出失败:\n{str(e)}")

    def _on_save_clicked(self):
        """Save the chip definition to <data dir>/<name>.yaml and register it"""
        chip = self._build_current_chip()
        if not CHIP_NAME_PATTERN.match(chip.name) or chip.name == "UNNAMED_CHIP":
            QMessageBox.warning(
                self, "验证失败",
                "请输入有效的芯片型号名称！\n仅允许字母、数字、下划线、点和连字符，且不能以符号开头。"
            )
            self.tabs.setCurrentIndex(0)
            self.name_edit.setFocus()
            return

        dups = self.pin_model.duplicates()
        if dups:
            listed = ", ".join(f"{port}/{pin}" for port, pin in sorted(dups)[:10])
            QMessageBox.warning(self, "引脚重复", f"以下引脚重复定义（已标红），请修正后再保存:\n{listed}")
            self.tabs.setCurrentIndex(2)
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

        try:
            self._selectors_from_table()
        except ValueError as e:
            QMessageBox.warning(self, "选择器无效", str(e))
            self.tabs.setCurrentIndex(0)
            return

        try:
            self.peripheral_editor.validated_resources()
        except ValueError as e:
            QMessageBox.warning(self, "外设实例无效", str(e))
            self.tabs.setCurrentIndex(1)
            return

        pending = count_placeholders(chip.ecu_resources)
        if pending:
            reply = QMessageBox.question(
                self,
                "ECU 资源待填写",
                f"仍有 {pending} 个 ECU 资源条目的值为空（待填写）。\n"
                "空值会让 ecu:get() 得到空结果，确定要保存吗？",
                QMessageBox.Yes | QMessageBox.No,
                QMessageBox.No
            )
            if reply != QMessageBox.Yes:
                self.ecu_editor.filter_combo.setCurrentIndex(1)     # show only the entries to fill in
                self.tabs.setCurrentIndex(3)
                return

        target_file = self._get_save_dir() / f"{chip.name}.yaml"
        is_own_file = chip.name == self._editing_name
        if not is_own_file and (target_file.exists() or self.chip_database.get_chip(chip.name)):
            reply = QMessageBox.question(
                self, "覆盖确认",
                f"芯片 {chip.name} 已存在于芯片库中，是否覆盖？\n{target_file}",
                QMessageBox.Yes | QMessageBox.No, QMessageBox.No
            )
            if reply != QMessageBox.Yes:
                return

        try:
            self.exporter.save_yaml(chip, target_file)
        except Exception as e:
            logger.exception("Failed to save chip definition")
            QMessageBox.critical(self, "保存错误", f"保存芯片定义失败:\n{str(e)}")
            return

        self.chip_database.register_chip(copy.deepcopy(chip))
        self._base_chip = copy.deepcopy(chip)
        self._editing_name = chip.name
        self._last_saved_chip = chip.name
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

    def reject(self):
        """Closing after a successful save reports Accepted so callers using exec() refresh"""
        if self._last_saved_chip:
            self.accept()
        else:
            super().reject()

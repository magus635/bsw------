"""
New Project Wizard

A multi-step QWizard that guides users through creating a new AUTOSAR project:
  Page 1: Project basic info (name, type, folder)
  Page 2: Chip selection (from database / open designer / import YAML)
  Page 3: Summary and confirmation
"""
from pathlib import Path
from typing import Dict, List, Optional, Any
import logging

from PySide6.QtWidgets import (
    QWizard, QWizardPage, QVBoxLayout, QHBoxLayout, QFormLayout,
    QLabel, QLineEdit, QComboBox, QPushButton, QGroupBox, QWidget,
    QFileDialog, QMessageBox, QListWidget, QListWidgetItem,
    QTextEdit, QCheckBox, QSplitter, QAbstractItemView, QFrame
)
from PySide6.QtCore import Qt, Signal
from PySide6.QtGui import QFont, QIcon

from ...core.config_manager import ProjectType
from ...core.hardware.chip_database import ChipDatabase, ChipDefinition

logger = logging.getLogger(__name__)


class ProjectInfoPage(QWizardPage):
    """Page 1: Project name, type, and folder selection"""

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setTitle("项目基本信息 (Project Information)")
        self.setSubTitle("设置新项目的名称、类型和存储位置。")

        self._folder_path: Optional[Path] = None
        self._setup_ui()

    def _setup_ui(self):
        layout = QVBoxLayout(self)
        layout.setSpacing(14)

        form_group = QGroupBox("项目设置 (Project Settings)")
        form = QFormLayout(form_group)
        form.setLabelAlignment(Qt.AlignRight)
        form.setHorizontalSpacing(12)
        form.setVerticalSpacing(12)
        form.setFieldGrowthPolicy(QFormLayout.ExpandingFieldsGrow)

        # Project name
        self.name_edit = QLineEdit()
        self.name_edit.setPlaceholderText("例: MyAutosar_Project")
        self.name_edit.textChanged.connect(self.completeChanged)
        form.addRow("项目名称 (Name)*:", self.name_edit)

        # Register as wizard field for cross-page access
        self.registerField("project_name*", self.name_edit)

        # Project type
        self.type_combo = QComboBox()
        self.type_combo.addItem("EB Tresos", ProjectType.EB_TRESOS)
        self.type_combo.addItem("Vector DaVinci", ProjectType.VECTOR)
        form.addRow("项目类型 (Type):", self.type_combo)

        layout.addWidget(form_group)

        # Folder selection
        folder_group = QGroupBox("项目路径 (Project Location)")
        folder_layout = QHBoxLayout(folder_group)

        self.folder_label = QLabel("未选择文件夹")
        self.folder_label.setStyleSheet("color: #888; padding: 4px;")
        self.folder_label.setWordWrap(True)
        folder_layout.addWidget(self.folder_label, 1)

        browse_btn = QPushButton("📂 浏览... (Browse)")
        browse_btn.setStyleSheet("padding: 5px 12px;")
        browse_btn.clicked.connect(self._on_browse_folder)
        folder_layout.addWidget(browse_btn)

        layout.addWidget(folder_group)

        # Hint
        hint_label = QLabel(
            "💡 <b>提示</b>: 建议为每个项目创建一个独立的空文件夹。"
            "项目文件 (.dpa) 和配置文件将保存在此目录下。"
        )
        hint_label.setWordWrap(True)
        hint_label.setStyleSheet("color: #666; font-size: 12px; margin-top: 8px;")
        layout.addWidget(hint_label)

        layout.addStretch()

    def _on_browse_folder(self):
        folder = QFileDialog.getExistingDirectory(
            self, "选择项目目录 (Select Project Folder)",
            str(Path.home()), QFileDialog.ShowDirsOnly
        )
        if folder:
            self._folder_path = Path(folder)
            self.folder_label.setText(str(self._folder_path))
            self.folder_label.setStyleSheet("color: #2b579a; padding: 4px; font-weight: bold;")
            self.completeChanged.emit()

    def isComplete(self) -> bool:
        return bool(self.name_edit.text().strip()) and self._folder_path is not None

    def get_project_name(self) -> str:
        return self.name_edit.text().strip()

    def get_project_type(self) -> ProjectType:
        return self.type_combo.currentData()

    def get_folder_path(self) -> Optional[Path]:
        return self._folder_path


class ChipSelectionPage(QWizardPage):
    """Page 2: Select, import, or create chip definition"""

    def __init__(self, chip_database: ChipDatabase, parent=None):
        super().__init__(parent)
        self.chip_database = chip_database
        self.setTitle("选择目标芯片 (Select Target Chip)")
        self.setSubTitle("选择您的项目所使用的 MCU 芯片型号。这将激活硬件约束校验。")

        self._selected_chip_name: Optional[str] = None
        self._setup_ui()
        self._populate_chip_list()

    def _setup_ui(self):
        layout = QVBoxLayout(self)
        layout.setSpacing(10)

        # Chip list + info splitter
        splitter = QSplitter(Qt.Horizontal)

        # Left: chip list
        left_widget = QWidget()
        left_layout = QVBoxLayout(left_widget)
        left_layout.setContentsMargins(0, 0, 0, 0)

        list_label = QLabel("芯片库 (Chip Library):")
        list_label.setStyleSheet("font-weight: bold;")
        left_layout.addWidget(list_label)

        self.chip_list = QListWidget()
        self.chip_list.setSelectionMode(QAbstractItemView.SingleSelection)
        self.chip_list.currentItemChanged.connect(self._on_chip_selected)
        left_layout.addWidget(self.chip_list, 1)

        # Action buttons
        btn_layout = QHBoxLayout()

        import_btn = QPushButton("📂 导入 YAML...")
        import_btn.setToolTip("从 YAML 文件导入芯片定义")
        import_btn.clicked.connect(self._on_import_yaml)
        btn_layout.addWidget(import_btn)

        new_btn = QPushButton("🆕 新建芯片...")
        new_btn.setToolTip("打开芯片定义设计器创建新芯片")
        new_btn.setStyleSheet("font-weight: bold;")
        new_btn.clicked.connect(self._on_create_new_chip)
        btn_layout.addWidget(new_btn)

        left_layout.addLayout(btn_layout)
        splitter.addWidget(left_widget)

        # Right: chip info preview
        right_widget = QWidget()
        right_layout = QVBoxLayout(right_widget)
        right_layout.setContentsMargins(0, 0, 0, 0)

        info_label = QLabel("芯片信息 (Chip Info):")
        info_label.setStyleSheet("font-weight: bold;")
        right_layout.addWidget(info_label)

        self.chip_info = QTextEdit()
        self.chip_info.setReadOnly(True)
        self.chip_info.setFont(QFont("Menlo, Monaco, Consolas, Courier New", 10))
        self.chip_info.setPlaceholderText("请从左侧列表选择一个芯片以查看详情...")
        right_layout.addWidget(self.chip_info, 1)
        splitter.addWidget(right_widget)

        splitter.setSizes([300, 400])
        layout.addWidget(splitter, 1)

        # "Skip" option
        self.skip_check = QCheckBox("暂不选择芯片，稍后通过 项目属性 设置 (Skip chip selection)")
        self.skip_check.stateChanged.connect(self._on_skip_toggled)
        self.skip_check.stateChanged.connect(self.completeChanged)
        layout.addWidget(self.skip_check)

    def _populate_chip_list(self):
        """Fill chip list from database"""
        self.chip_list.clear()
        chips = self.chip_database.list_chips()

        for chip_name in chips:
            chip = self.chip_database.get_chip(chip_name)
            if chip:
                label = f"{chip.name}"
                if chip.family:
                    label += f"  [{chip.family}]"
                if chip.package:
                    label += f"  ({chip.package})"

                item = QListWidgetItem(label)
                item.setData(Qt.UserRole, chip.name)
                self.chip_list.addItem(item)

        if not chips:
            empty_item = QListWidgetItem("（芯片库为空，请点击下方按钮导入或新建）")
            empty_item.setFlags(empty_item.flags() & ~Qt.ItemIsSelectable)
            empty_item.setForeground(Qt.gray)
            self.chip_list.addItem(empty_item)

    def _on_chip_selected(self, current, previous):
        """Show chip details when selected"""
        if not current:
            self._selected_chip_name = None
            self.chip_info.clear()
            self.completeChanged.emit()
            return

        chip_name = current.data(Qt.UserRole)
        if not chip_name:
            return

        self._selected_chip_name = chip_name
        chip = self.chip_database.get_chip(chip_name)
        if chip:
            self._show_chip_info(chip)

        self.completeChanged.emit()

    def _show_chip_info(self, chip: ChipDefinition):
        """Display chip summary in info panel"""
        total_pins = sum(len(pins) for pins in chip.ports.values())
        info_lines = [
            f"芯片型号: {chip.name}",
            f"芯片系列: {chip.family}",
            f"封装规格: {chip.package}",
            f"描述: {chip.description}",
            "",
            f"=== 硬件资源 ===",
            f"端口数量: {len(chip.ports)}",
            f"引脚总数: {total_pins}",
        ]

        if chip.can_resources:
            can_names = ", ".join(c.name for c in chip.can_resources)
            fd_support = "是" if any(c.supports_fd for c in chip.can_resources) else "否"
            info_lines.append(f"CAN 控制器: {len(chip.can_resources)} ({can_names})")
            info_lines.append(f"  CAN-FD 支持: {fd_support}")

        if chip.adc_resources:
            adc_names = ", ".join(a.name for a in chip.adc_resources)
            info_lines.append(f"ADC 单元: {len(chip.adc_resources)} ({adc_names})")

        if chip.spi_resources:
            spi_names = ", ".join(s.name for s in chip.spi_resources)
            info_lines.append(f"SPI 模块: {len(chip.spi_resources)} ({spi_names})")

        if chip.ports:
            info_lines.append("")
            info_lines.append("=== 端口列表 ===")
            for port_name in sorted(chip.ports.keys()):
                pins = chip.ports[port_name]
                info_lines.append(f"  {port_name}: {len(pins)} 个引脚")

        self.chip_info.setPlainText("\n".join(info_lines))

    def _on_import_yaml(self):
        """Import chip definition from YAML file"""
        file_path, _ = QFileDialog.getOpenFileName(
            self, "导入芯片定义 (Import Chip YAML)",
            str(Path.home()),
            "YAML Files (*.yaml *.yml);;All Files (*)"
        )
        if not file_path:
            return

        try:
            chip = self.chip_database._load_chip_from_yaml(Path(file_path))
            if chip:
                self.chip_database.register_chip(chip)
                self._populate_chip_list()

                # Auto-select the imported chip
                for i in range(self.chip_list.count()):
                    item = self.chip_list.item(i)
                    if item.data(Qt.UserRole) == chip.name:
                        self.chip_list.setCurrentItem(item)
                        break

                QMessageBox.information(
                    self, "导入成功",
                    f"已成功导入芯片: {chip.name}\n({chip.family} / {chip.package})"
                )
            else:
                QMessageBox.warning(self, "导入失败", "YAML 文件格式错误或缺少 'name' 字段。")
        except Exception as e:
            QMessageBox.critical(self, "导入错误", f"无法解析 YAML 文件:\n{str(e)}")

    def _on_create_new_chip(self):
        """Open Chip Definition Designer dialog"""
        from ..dialogs.chip_definition_designer_dialog import ChipDefinitionDesignerDialog

        dialog = ChipDefinitionDesignerDialog(
            chip_database=self.chip_database, parent=self
        )
        if dialog.exec():
            self._populate_chip_list()
            # Auto-select newly created chip
            if dialog._last_saved_chip:
                for i in range(self.chip_list.count()):
                    item = self.chip_list.item(i)
                    if item.data(Qt.UserRole) == dialog._last_saved_chip:
                        self.chip_list.setCurrentItem(item)
                        break

    def _on_skip_toggled(self, state):
        """Handle skip checkbox toggle"""
        self.chip_list.setEnabled(state != Qt.Checked.value)

    def isComplete(self) -> bool:
        if self.skip_check.isChecked():
            return True
        return self._selected_chip_name is not None

    def get_selected_chip(self) -> Optional[str]:
        if self.skip_check.isChecked():
            return None
        return self._selected_chip_name


class ProjectSummaryPage(QWizardPage):
    """Page 3: Summary and confirmation"""

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setTitle("创建确认 (Confirmation)")
        self.setSubTitle("请确认以下项目设置。点击「完成」创建项目。")
        self._setup_ui()

    def _setup_ui(self):
        layout = QVBoxLayout(self)

        self.summary_text = QTextEdit()
        self.summary_text.setReadOnly(True)
        self.summary_text.setFont(QFont("Menlo, Monaco, Consolas, Courier New", 11))
        layout.addWidget(self.summary_text, 1)

        # Next step hint
        hint_group = QGroupBox("🎯 创建后的下一步操作 (Next Steps)")
        hint_layout = QVBoxLayout(hint_group)
        hint_layout.addWidget(QLabel(
            "1. 通过 <b>File → Add Module</b> 添加 BSW 模块 (如 Can, Dio, Spi, Mcu 等)\n"
            "2. 在左侧树中选择模块，展开容器进行参数配置\n"
            "3. 使用 <b>Wizards → Hardware Mapping</b> 进行引脚映射\n"
            "4. 使用 <b>File → Save Project</b> (Ctrl+S) 保存项目"
        ))
        layout.addWidget(hint_group)

    def initializePage(self):
        """Called when this page is shown — gather data from previous pages"""
        wizard = self.wizard()
        if not isinstance(wizard, NewProjectWizard):
            return

        info_page = wizard.info_page
        chip_page = wizard.chip_page

        name = info_page.get_project_name()
        proj_type = info_page.get_project_type()
        folder = info_page.get_folder_path()
        chip = chip_page.get_selected_chip()

        lines = [
            "╔══════════════════════════════════════════╗",
            "║         新项目摘要 (Project Summary)         ║",
            "╚══════════════════════════════════════════╝",
            "",
            f"  项目名称:  {name}",
            f"  项目类型:  {proj_type.value if proj_type else 'Unknown'}",
            f"  保存路径:  {folder}",
            f"  项目文件:  {folder / f'{name}.dpa' if folder else 'N/A'}",
            "",
            f"  目标芯片:  {chip or '（未选择，稍后设置）'}",
        ]

        if chip:
            chip_def = wizard.chip_database.get_chip(chip)
            if chip_def:
                total_pins = sum(len(p) for p in chip_def.ports.values())
                lines.extend([
                    f"    芯片系列: {chip_def.family}",
                    f"    封装规格: {chip_def.package}",
                    f"    端口/引脚: {len(chip_def.ports)} 个端口, {total_pins} 个引脚",
                    f"    CAN: {len(chip_def.can_resources)} 个控制器",
                    f"    ADC: {len(chip_def.adc_resources)} 个单元",
                    f"    SPI: {len(chip_def.spi_resources)} 个模块",
                ])

        self.summary_text.setPlainText("\n".join(lines))


class NewProjectWizard(QWizard):
    """
    Multi-step wizard guiding users through new project creation.

    Pages:
      1. Project info (name, type, folder)
      2. Chip selection (from database / import / designer)
      3. Summary confirmation
    """

    project_created = Signal(dict)  # Emits result dict on successful creation

    def __init__(self, chip_database: Optional[ChipDatabase] = None, parent=None):
        super().__init__(parent)
        self.setWindowTitle("新建项目向导 (New Project Wizard)")
        self.setWizardStyle(QWizard.ModernStyle)
        self.setOption(QWizard.HaveHelpButton, False)
        self.setMinimumSize(700, 520)

        # Resolve chip database
        if chip_database:
            self.chip_database = chip_database
        else:
            pkg_dir = Path(__file__).resolve().parent.parent.parent
            data_dir = pkg_dir / "data" / "chips"
            data_dir.mkdir(parents=True, exist_ok=True)
            self.chip_database = ChipDatabase(data_dir)

        self._setup_pages()

    def _setup_pages(self):
        self.info_page = ProjectInfoPage()
        self.chip_page = ChipSelectionPage(self.chip_database)
        self.summary_page = ProjectSummaryPage()

        self.addPage(self.info_page)
        self.addPage(self.chip_page)
        self.addPage(self.summary_page)

    def get_result(self) -> Dict[str, Any]:
        """Collect wizard result data"""
        return {
            "project_name": self.info_page.get_project_name(),
            "project_type": self.info_page.get_project_type(),
            "folder_path": self.info_page.get_folder_path(),
            "selected_chip": self.chip_page.get_selected_chip(),
        }

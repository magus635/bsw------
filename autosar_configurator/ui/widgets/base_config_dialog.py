"""
Base Configuration Dialog
Allows users to create and modify Base configuration
"""
from PySide6.QtWidgets import (
    QDialog, QVBoxLayout, QHBoxLayout, QLabel, QPushButton,
    QRadioButton, QButtonGroup, QGroupBox, QMessageBox
)
from PySide6.QtCore import Qt


class BaseConfigDialog(QDialog):
    """Dialog for creating/modifying Base configuration"""
    
    def __init__(self, parent=None, is_modify=False):
        super().__init__(parent)
        self.is_modify = is_modify
        self.selected_method = "arxml"  # Default
        
        self.setWindowTitle("修改 Base 配置" if is_modify else "创建 Base 配置")
        self.setMinimumWidth(400)
        self.setup_ui()
    
    def setup_ui(self):
        layout = QVBoxLayout(self)
        
        # Description
        if self.is_modify:
            desc = QLabel("选择如何更新 Base 配置：")
        else:
            desc = QLabel("Base 是所有变体的基准配置。\n选择如何初始化 Base：")
        desc.setWordWrap(True)
        layout.addWidget(desc)
        
        # Options group
        options_group = QGroupBox("初始化方式")
        options_layout = QVBoxLayout(options_group)
        
        self.btn_group = QButtonGroup(self)
        
        # Option 1: From ARXML
        self.radio_arxml = QRadioButton("从 ARXML 配置文件 (当前已加载的配置值)")
        self.radio_arxml.setToolTip("使用当前项目中各模块的 ARXML 配置值作为 Base")
        self.radio_arxml.setChecked(True)
        self.btn_group.addButton(self.radio_arxml, 1)
        options_layout.addWidget(self.radio_arxml)
        
        # Option 2: From Defaults
        self.radio_defaults = QRadioButton("从定义文件默认值 (XDM 中的 default-value)")
        self.radio_defaults.setToolTip("使用参数定义文件中的默认值作为 Base")
        self.btn_group.addButton(self.radio_defaults, 2)
        options_layout.addWidget(self.radio_defaults)
        
        # Option 3: Empty
        self.radio_empty = QRadioButton("空白 (手动配置所有参数)")
        self.radio_empty.setToolTip("创建空的 Base，所有参数需要手动设置")
        self.btn_group.addButton(self.radio_empty, 3)
        options_layout.addWidget(self.radio_empty)
        
        layout.addWidget(options_group)
        
        # Buttons
        btn_layout = QHBoxLayout()
        btn_layout.addStretch()
        
        cancel_btn = QPushButton("取消")
        cancel_btn.clicked.connect(self.reject)
        btn_layout.addWidget(cancel_btn)
        
        ok_btn = QPushButton("确定")
        ok_btn.setDefault(True)
        ok_btn.clicked.connect(self.accept)
        btn_layout.addWidget(ok_btn)
        
        layout.addLayout(btn_layout)
    
    def get_selected_method(self) -> str:
        """Return selected initialization method"""
        checked_id = self.btn_group.checkedId()
        if checked_id == 1:
            return "arxml"
        elif checked_id == 2:
            return "defaults"
        else:
            return "empty"

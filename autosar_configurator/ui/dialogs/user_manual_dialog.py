"""
User Manual Dialog
Displays comprehensive application documentation in Markdown.
"""
from PySide6.QtWidgets import QDialog, QVBoxLayout, QTextBrowser, QDialogButtonBox
from PySide6.QtCore import Qt

USER_MANUAL_MD = """
# DaVinci Configurator 使用手册

欢迎使用 DaVinci Configurator 图形化配置工具。本手册旨在帮助您熟练掌握工具的各项功能。

## 1. 项目与模块管理
*   **新建项目**: 通过 `File -> New Project` 创建。
*   **打开/保存**: 支持加载 ARXML、JSON 格式的项目文件。
*   **模块导入**: 在树状视图顶部点击 `+` 或右键从 `Module -> Import` 加载 `.epd` 定义文件。
*   **属性编辑**: 菜单 `Project -> Properties` 可修改项目元数据（名称、版本、作者等）。

## 2. 配置编辑与引用管理
*   **双模式树视图**: 
    *   **📋 定义层**: 灰色斜体显示，代表 AUTOSAR 标准定义。
    *   **✅ 实例层**: 加粗显示，代表您的具体配置。
*   **容器操作**: 右键点击定义层可 `Add Instance`；点击实例层可 `Delete`。
*   **参数编辑**: 右侧面板显示容器的所有参数，支持数值验证、下拉选择。
*   **引用跳转**: 在引用（Reference）面板，点击目标后的跳转按钮可直接定位到被引用的容器。

## 3. 验证系统 (Validation)
*   **实时验证**: 编辑参数时，工具会自动检查：
    *   数值范围（Min/Max）
    *   正则表达式匹配
    *   必填项检查
*   **规则管理**: 菜单 `Project -> Rule Manager` 可查看和自定义验证规则。
*   **错误预览**: 状态栏和树状视图会通过图标标记验证失败的项目。

## 4. 代码生成 (Code Generation)
*   **生成选项**: 菜单 `Generate -> Generate All` 或 `Generate Module`。
*   **模板引擎**:
    *   **Standard (Jinja2)**: 适用于通用逻辑生成。
    *   **EB Tresos Compatible**: 深度兼容 EB 语法（支持 `[!LOOP!]`, `[!VAR!]`, `node:exists` 等）。
*   **类型标记**: 树状视图显示 `[EB]` (蓝色), `[Std]` (灰色), 或 `[Mixed]` (琥珀色) 来指示当前模块使用的引擎。悬停可看详情。

## 5. AI 智能辅助与高级功能
*   **AI 助手**: 点击右侧“AI Assistant”展开，支持自然语言对话修改配置。
*   **智能搜索**: 顶部搜索框支持属性、容器、参数的快速模糊匹配。
*   **影响分析**: 在参数编辑区点击“检查影响”，可分析修改该值对其他模块或引用的潜在后果。
*   **变体管理 (VT)**: 支持 Multi-variant 配置，一键切换不同变体组合。

## 6. 工具栏说明
*   💾 **保存**: 持久化当前配置。
*   🔍 **验证**: 全局一致性检查。
*   ⚡ **生成**: 触发代码生成流程。
*   🛠️ **设置**: 配置外部编译器或模板搜索路径。

---
*版本: v1.1.0 | 开发者团队: Antigravity AI*
"""

class UserManualDialog(QDialog):
    """Dialog showing the user manual"""
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("DaVinci Configurator 使用手册")
        self.setMinimumSize(800, 600)
        
        self._setup_ui()
    
    def _setup_ui(self):
        """Setup UI"""
        layout = QVBoxLayout(self)
        
        # Text browser for Markdown
        self.browser = QTextBrowser()
        self.browser.setMarkdown(USER_MANUAL_MD)
        self.browser.setOpenExternalLinks(True)
        layout.addWidget(self.browser)
        
        # Close button
        buttons = QDialogButtonBox(QDialogButtonBox.Close)
        buttons.rejected.connect(self.reject)
        layout.addWidget(buttons)

if __name__ == "__main__":
    # Test stub
    import sys
    from PySide6.QtWidgets import QApplication
    app = QApplication(sys.argv)
    dialog = UserManualDialog()
    dialog.show()
    sys.exit(app.exec())

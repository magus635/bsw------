"""
User Manual Dialog
Displays comprehensive application documentation in Markdown.
"""
from PySide6.QtWidgets import QDialog, QVBoxLayout, QTextBrowser, QDialogButtonBox
from PySide6.QtCore import Qt

USER_MANUAL_MD = """
# DaVinci Configurator 使用手册

欢迎使用 DaVinci Configurator 图形化配置工具。本手册旨在帮助您熟练掌握工具的各项功能。

---

## 1. 快捷键速查表

### 文件操作
| 功能 | Windows/Linux | macOS |
|------|---------------|-------|
| 新建项目 | Ctrl+Shift+N | Cmd+Shift+N |
| 打开项目 | Ctrl+Shift+O | Cmd+Shift+O |
| 保存项目 | Ctrl+Shift+S | Cmd+Shift+S |
| 新建配置 | Ctrl+N | Cmd+N |
| 打开定义文件 | Ctrl+O | Cmd+O |
| 保存配置 | Ctrl+S | Cmd+S |
| 退出 | Ctrl+Q | Cmd+Q |

### 编辑操作
| 功能 | Windows/Linux | macOS |
|------|---------------|-------|
| 撤销 | Ctrl+Z | Cmd+Z |
| 重做 | Ctrl+Y | Cmd+Shift+Z |
| 复制 | Ctrl+C | Cmd+C |
| 粘贴 | Ctrl+V | Cmd+V |

### 工具与视图
| 功能 | Windows/Linux | macOS |
|------|---------------|-------|
| 验证配置 | Ctrl+Shift+V | Cmd+Shift+V |
| 代码生成 | Ctrl+G | Cmd+G |
| 搜索 | Ctrl+F | Cmd+F |
| 依赖关系图 | Ctrl+D | Cmd+D |
| AI 助手 | Ctrl+Shift+A | Cmd+Shift+A |
| 使用手册 | F1 | F1 |

---

## 2. 项目与模块管理

### 2.1 项目操作
*   **新建项目**: `File -> New Project` 或 `Ctrl+Shift+N`
*   **打开项目**: `File -> Open Project` 或 `Ctrl+Shift+O`，支持 `.dpa` 项目文件
*   **保存项目**: `File -> Save Project` 或 `Ctrl+Shift+S`

### 2.2 模块定义文件
*   **打开定义**: `File -> Open Definition (.epd)` 加载模块定义文件
*   **定义文件来源**:
    *   EB Tresos 安装目录: `<EB_ROOT>/plugins/<Module>/config/`
    *   AUTOSAR 工具链提供的 `.arxml` 定义文件
*   **支持格式**: `.epd` (EB Tresos), `.arxml` (AUTOSAR 标准)

### 2.3 配置文件
*   **新建配置**: `File -> New Value File` 或 `Ctrl+N`
*   **保存配置**: `File -> Save Value File` 或 `Ctrl+S`
*   **属性编辑**: `Project -> Properties` 修改项目元数据

---

## 3. 配置编辑与引用管理

### 3.1 双模式树视图
*   **定义层 (灰色斜体)**: AUTOSAR 标准定义，不可直接编辑
*   **实例层 (加粗)**: 您的具体配置实例

### 3.2 容器操作
*   **添加实例**: 右键定义层容器 -> `Add Instance`
*   **删除实例**: 右键实例层容器 -> `Delete`
*   **复制/粘贴**: 选中容器后 `Ctrl+C` / `Ctrl+V`

### 3.3 参数编辑
*   选中容器后，右侧面板显示所有参数
*   支持的参数类型：
    *   **STRING**: 文本输入
    *   **INTEGER/FLOAT**: 数值输入，支持范围验证
    *   **BOOLEAN**: 开关选择
    *   **ENUM**: 下拉选择
    *   **ARRAY**: 逗号分隔的多值输入
    *   **REFERENCE**: 智能引用选择器

### 3.4 引用管理
*   引用面板显示当前容器的所有引用关系
*   点击跳转按钮可定位到被引用的容器
*   引用解析状态图标：
    *   ✅ 绿色: 解析成功
    *   ⚠️ 黄色: 目标不存在
    *   ❌ 红色: 路径格式错误

---

## 4. 撤销/重做 (Undo/Redo)

本工具支持完整的撤销重做功能：
*   **撤销**: `Ctrl+Z` (Windows) / `Cmd+Z` (macOS)
*   **重做**: `Ctrl+Y` (Windows) / `Cmd+Shift+Z` (macOS)
*   支持的操作：参数修改、容器增删、引用变更等

---

## 5. 验证系统 (Validation)

### 5.1 实时验证
编辑参数时自动检查：
*   数值范围 (Min/Max)
*   正则表达式匹配
*   必填项检查
*   引用目标有效性

### 5.2 全局验证
*   菜单 `Project -> Validate All` 或 `Ctrl+Shift+V`
*   验证结果在底部面板显示

### 5.3 错误标记
*   树视图中错误项显示红色图标
*   状态栏显示错误计数
*   双击错误可跳转到问题位置

---

## 6. 代码生成 (Code Generation)

### 6.1 生成操作
*   **生成全部**: 菜单 `Generate -> Generate All` 或 `Ctrl+G`
*   **生成单模块**: 右键模块 -> `Generate Code`

### 6.2 模板引擎
*   **EB Tresos Compatible**:
    *   支持 `[!IF]`, `[!ELSE]`, `[!LOOP]`, `[!SELECT]`, `[!VAR]`
    *   内置函数: `node:value()`, `node:ref()`, `num:inttohex()` 等
*   **Standard (Jinja2)**: 通用 Python 模板语法

### 6.3 输出文件
*   `<Module>_Cfg.h`: 预编译配置头文件
*   `<Module>_Lcfg.c`: 链接时配置
*   `<Module>_PBcfg.c`: 后构建配置
*   输出目录: 项目属性中配置，默认为 `./output/<Module>/`

### 6.4 模板类型标记
*   `[EB]` 蓝色: 使用 EB Tresos 模板
*   `[Std]` 灰色: 使用 Jinja2 模板
*   `[Mixed]` 琥珀色: 混合使用

---

## 7. AI 智能辅助

### 7.1 配置要求
使用 AI 功能前需配置 Google Gemini API Key：
1. 获取 API Key: https://makersuite.google.com/app/apikey
2. 设置环境变量: `export GEMINI_API_KEY="your-api-key"`
3. 或打开 `View -> AI Assistant`，点击面板右上角 `Settings`

### 7.2 功能说明
*   **AI 助手面板**: `Ctrl+Shift+A` 打开/关闭
*   **自然语言查询**: 输入问题获取配置建议
*   **错误诊断**: AI 分析验证错误并提供修复方案
*   **配置推荐**: 基于上下文推荐参数值

### 7.3 智能搜索
*   `Ctrl+F` 打开搜索框
*   支持正则表达式
*   可按类型过滤 (容器/参数/引用)

---

## 8. 高级功能

### 8.1 依赖关系图
*   `Ctrl+D` 打开可视化依赖图
*   显示模块间的引用关系
*   支持缩放和拖拽

### 8.2 批量编辑
1. 在树视图中按住 `Ctrl` 多选容器
2. 右键选择 `Batch Edit`
3. 在弹出对话框中修改共同属性

### 8.3 变体管理 (Variant)
*   `Project -> Variant Management` 打开变体管理器
*   支持创建多个配置变体
*   一键切换变体组合

### 8.4 影响分析
*   在参数编辑区点击"检查影响"按钮
*   分析修改该值对其他模块的潜在影响

---

## 9. 故障排除

### 常见问题

**Q: 应用启动失败**
*   检查 Python 版本 >= 3.10
*   运行 `pip install -r requirements.txt` 重新安装依赖

**Q: 无法加载 .epd 文件**
*   确认文件格式正确 (XML)
*   检查文件编码为 UTF-8

**Q: 代码生成失败**
*   检查模板文件路径是否正确
*   查看生成日志获取详细错误信息

**Q: AI 助手无响应**
*   确认已配置 GEMINI_API_KEY 环境变量
*   检查网络连接

**Q: 引用解析失败**
*   确认引用目标路径格式正确
*   检查被引用的容器是否存在

---

## 10. 界面布局

```
+----------------------------------------------------------+
| File  Edit  Project  Generate  View  Help                |
+----------------------------------------------------------+
| [New] [Open] [Save] | [Validate] [Generate] | [Search]   |
+------------------+---------------------------------------+
|                  |                                       |
|  Module Tree     |  Configuration Panel                  |
|  +-----------+   |  +-------------------------------+    |
|  | Adc       |   |  | Container: AdcGeneral        |    |
|  |  +-Cfg    |   |  | +---------------------------+ |    |
|  |  +-Channel|   |  | | AdcDevErrorDetect: true   | |    |
|  | Can       |   |  | | AdcVersionInfoApi: false  | |    |
|  |  +-Ctrl   |   |  | +---------------------------+ |    |
|  +-----------+   |  +-------------------------------+    |
|                  |                                       |
|                  +---------------------------------------+
|                  |  AI Assistant (Ctrl+Shift+A)          |
|                  |  +-------------------------------+    |
|                  |  | Ask me anything...            |    |
|                  |  +-------------------------------+    |
+------------------+---------------------------------------+
| Status: Ready | Errors: 0 | Warnings: 2                  |
+----------------------------------------------------------+
```

---

*版本: v2.0.0 | 基于 AUTOSAR 4.4.0 标准*
*技术支持: 查看项目 README.md 或提交 Issue*
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

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

### 文件与工程操作
| 功能 | Windows/Linux | macOS | 菜单路径 |
|------|---------------|-------|----------|
| 新建项目 | Ctrl+Shift+N | Cmd+Shift+N | `File -> New Project...` |
| 打开项目 | Ctrl+Shift+O | Cmd+Shift+O | `File -> Open Project...` |
| 保存项目 | Ctrl+Shift+S | Cmd+Shift+S | `File -> Save Project` |
| 工程属性 | - | - | `File -> Project Properties...` |
| 变体管理 | - | - | `File -> Manage Variants...` |
| 导入 EB 工程 | - | - | `File -> Import -> Import EB Tresos Project...` |
| 导入值文件 | - | - | `File -> Import -> Import Value File...` |
| 导入外部数据表 | Ctrl+I | Cmd+I | `File -> Import -> Import from Excel / CSV / DBC...` |
| 导出 EPC 文件 | - | - | `File -> Export -> Export EPC Files...` |

### 编辑与容器操作
| 功能 | Windows/Linux | macOS | 菜单路径 |
|------|---------------|-------|----------|
| 撤销 (Undo) | Ctrl+Z | Cmd+Z | `Edit -> Undo` |
| 重做 (Redo) | Ctrl+Y / Ctrl+Shift+Z | Cmd+Shift+Z | `Edit -> Redo` |
| 复制容器 | Ctrl+C | Cmd+C | `Edit -> Copy` |
| 粘贴容器 | Ctrl+V | Cmd+V | `Edit -> Paste` |
| 验证配置 | Ctrl+Shift+V | Cmd+Shift+V | `Edit -> Validate Configuration` |
| 加载自定义规则 | - | - | `Edit -> Load Custom Rules...` |

### 生成、分析与视图
| 功能 | Windows/Linux | macOS | 菜单路径 |
|------|---------------|-------|----------|
| 代码生成 | Ctrl+G | Cmd+G | `Generate -> Generate Code` |
| 通信配置工作台 | - | - | `Tools -> 通信配置工作台...` / 左侧导航 `📡 通信配置` / 树右键通信模块 |
| RTE / SchM 工作台 | - | - | `Generate -> RTE / SchM 工作台...` / `Tools -> RTE / SchM 工作台...` / 树右键 `Rte`（含 SchM、SWC 数据映射、服务端口与 `Rte.c` 多核生成） |
| 跨模块依赖分析 | - | - | `Analysis -> 🔍 分析跨模块依赖...` |
| 跨模块依赖验证 | - | - | `Analysis -> ✅ 验证跨模块依赖...` |
| 依赖关系图 | Ctrl+D | Cmd+D | `View -> Dependency Graph` / `Analysis` |
| 智能搜索面板 | Ctrl+F | Cmd+F | `View -> Search...` |
| 左侧功能导航栏显隐 | - | - | `View -> Navigation Bar` |
| AI 智能助手 | Ctrl+Shift+A | Cmd+Shift+A | `View -> AI Assistant` |

### 向导工具 (Wizards)
| 功能 | Windows/Linux | macOS | 菜单路径 |
|------|---------------|-------|----------|
| 快速配置向导 | Ctrl+Q | Cmd+Q | `Wizards -> Quick Configuration...` |
| 批量创建向导 | Ctrl+Shift+B | Cmd+Shift+B | `Wizards -> Batch Create...` |
| 硬件映射向导 | Ctrl+Shift+H | Cmd+Shift+H | `Wizards -> Hardware Mapping...` |
| 应用模板向导 | Ctrl+T | Cmd+T | `Wizards -> Apply Template...` |
| 数据导入向导 | Ctrl+I | Cmd+I | `Wizards -> Import from Excel / CSV / DBC...` |
| 使用手册 | F1 | F1 | `Help -> 使用手册 (User Manual)` |

---

## 2. 项目与模块管理

### 2.1 项目工作流
本工具统一采用**项目工作流**（基于 `.dpa` 工程文件）：
*   **新建项目**: `File -> New Project...` (Ctrl+Shift+N)，可创建标准项目或初始化空项目。
*   **打开项目**: `File -> Open Project...` (Ctrl+Shift+O)，打开现有 `.dpa` 工程。
*   **保存项目**: `File -> Save Project` (Ctrl+Shift+S)，自动将模块定义、配置参数和芯片选择持久化。
*   **工程属性**: `File -> Project Properties...`，查看项目基本信息、创建时间、项目完整路径（支持一键复制与在访达中定位）、已配置模块总数及完整清单，并可切换目标 ECU/芯片型号。
*   **变体管理**: `File -> Manage Variants...`，配置并管理 AUTOSAR 配置变体（如 PreCompile / LinkTime / PostBuild）。

### 2.2 EB Tresos 工程导入
*   **批量导入**: 菜单 `File -> Import EB Tresos Project...`
*   自动扫描 EB Tresos 工程目录下的模块定义 (`.xdm`/`.epd`) 与实例值文件 (`.epc`/`.arxml`)。
*   如果工程包含多种芯片变体，支持在弹窗中选择目标芯片。
*   导入后自动将模板关联和硬件参数绑定到新工程中。

### 2.3 配置文件导入导出
*   **导入值文件**: `File -> Import Value File...`，用外部 `.epc` / `.arxml` / `.xdm` 替换当前选中模块的配置值。
*   **导出 EPC 文件**: `File -> Export EPC Files...`，将工程配置导出为 EB Tresos 完全兼容的标准 `.epc` 文件。

---

## 3. 配置编辑与引用管理

### 3.1 双模式树视图
*   **定义层 (灰色斜体)**: AUTOSAR 标准元模型定义，展示参数类型与约束，不可直接更改。
*   **实例层 (常规/加粗)**: 您的实际配置实例，可自由增删与修改参数。

### 3.2 容器操作
*   **添加实例**: 右键定义层容器 -> `Add Instance`
*   **删除实例**: 右键实例层容器 -> `Delete`
*   **复制/粘贴**: 选中容器后 `Ctrl+C` 复制，在父级容器上 `Ctrl+V` 粘贴
*   **多选批量操作**: 在树视图中支持多选容器进行批量删除或编辑。

### 3.3 参数编辑
选中容器后，右侧面板根据参数类型动态渲染对应编辑器：
*   **STRING**: 文本输入，支持正则与格式校验。
*   **INTEGER / FLOAT**: 数值输入，支持十六进制自动转换及 Min/Max 范围检查。
*   **BOOLEAN**: 复选框/开关选择。
*   **ENUM**: 下拉菜单选择合法枚举值。
*   **REFERENCE**: 智能引用选择器，支持树形选取目标容器并检查有效性。

### 3.4 引用管理与跳转
*   参数面板中带有引用跳转按钮，点击可快速在左侧树视图中高亮定位被引用节点。
*   引用状态标识：
    *   ✅ 绿色: 引用目标已成功解析
    *   ⚠️ 黄色: 目标容器尚未创建或路径失效
    *   ❌ 红色: 引用路径语法错误

---

## 4. 撤销/重做 (Undo / Redo)

本工具集成完整的撤销重做架构：
*   **撤销**: `Ctrl+Z` (macOS: `Cmd+Z`)
*   **重做**: `Ctrl+Y` / `Ctrl+Shift+Z` (macOS: `Cmd+Shift+Z`)
*   支持的操作覆盖参数修改、容器新建、实例删除、容器移动及引用变更。

---

## 5. 验证系统与跨模块分析

### 5.1 配置验证
*   **快捷执行**: 菜单 `Edit -> Validate Configuration` 或 `Ctrl+Shift+V`。
*   底部 **Problems View** 实时显示验证结果，分为错误 (Error)、警告 (Warning) 与信息 (Info)。
*   双击问题条目可直接跳转定位到对应的容器和参数。

### 5.2 跨模块依赖分析 (Analysis)
*   **分析跨模块依赖**: `Analysis -> 🔍 分析跨模块依赖...`，扫描诸如 MCU 时钟配置、PORT 引脚映射对 CAN/SPI/ADC 等外设模块的依赖链。
*   **验证跨模块依赖**: `Analysis -> ✅ 验证跨模块依赖...`，检查跨模块引用完整性。
*   **依赖关系图**: `View -> Dependency Graph` 或 `Ctrl+D`，以交互式图形可视化呈现模块间的相互依赖。

---

## 6. 代码生成 (Code Generation)

### 6.1 生成操作
*   **生成代码**: 菜单 `Generate -> Generate Code` 或快捷键 `Ctrl+G`。
*   状态栏实时反馈生成进度与输出文件位置。

### 6.2 模板机制
*   **安全原则**: 生成器**不使用内置默认模板**。仅当项目模板目录 (`templates/<ModuleName>/`) 或用户配置的模板目录中存在对应模板时才执行代码生成。
*   没有模板的模块会被安全跳过 (Skipped)，避免生成与目标硬件芯片不兼容的错误代码。
*   全面支持 EB Tresos 模板引擎语法（`[!IF]`、`[!LOOP]`、`[!SELECT]`、`[!MACRO]` 等）及常用内置 XPath 函数（`node:value()`、`node:ref()`、`ecu:get()`、`num:inttohex()` 等）。

### 6.3 RTE / SchM 图形化配置与生成工作台
当工程已加载 `Rte` 模块时，可通过 `Generate -> RTE / SchM 工作台...`、`Tools -> RTE / SchM 工作台...` 或在左侧模块树右键 `Rte` 选择 **`⚡ 打开 RTE / SchM 工作台...`** 启动专用 4 页签工作台：
*   **顶部健康检查快捷跳转条**：实时汇总未加载实例、未同步临界区、校验报错与未映射事件，支持一键跳转定位或直接补齐同步。
*   **1. BSW 实例与同步**：对照 `RteBswModuleInstance`、已加载模块与 `system/*_ib_bswmd.arxml`，支持一键补齐与清理残留。
*   **2. 临界区矩阵 (SchM)**：提供中英双语标签与悬停说明，支持就地与批量设置保护机制、`OsResource` / `OsSpinlock` 绑定及 `CUSTOM` 函数声明锁定。
*   **3. Task 调度映射**：左侧展示含 `SWC (只读)` 上下文的 `OsTask` 执行顺序与周期汇总（混合周期标橙预警），右侧支持 `Ctrl`/`Shift` 多选批量映射与按周期智能推荐 `OsTask`。
*   **4. 全局开关与生成预览**：明确区分“阶段 1 生效开关”与“ECUC 预留参数”，支持 C / Diff 语法高亮、`仅看差异 (Diff)` 对比、不重跑其余 BSW 的单独生成，以及一键跳转 **`在内存映射工作台中校验`** 形成 MemMap 校验闭环。
*   **安全修改与全局验证**：内置 **`使用说明 (?)`** 完整指南；修改前校验 Format 8 `PreLockedError` 基线锁，支持随时 **`恢复打开前状态`** / **`取消`** 回滚，点击 **`确定`** 后推入主窗口撤销栈（可用 `Ctrl+Z` / `Cmd+Z` 整批撤销）；执行 **`Ctrl+Shift+V` 全局验证**时，`RteSchmRule` 会在 **Problems** 面板列出就绪度与阶段 3 调度告警并支持双击直达工作台对应页签。

---

## 7. 向导功能 (Wizards)

*   **快速配置向导 (`Ctrl+Q`)**: 引导式完成常见基础模块初始化配置。
*   **批量创建向导 (`Ctrl+Shift+B`)**: 针对 Channel、Pin、Message 等大量重复实例，支持批量规则化创建。
*   **硬件映射向导 (`Ctrl+Shift+H`)**: 通用数据驱动机制，将目标芯片硬件资源（引脚、通道、时钟等）自动绑定到 AUTOSAR 配置。
*   **应用模板向导 (`Ctrl+T`)**: 将预设的标准配置方案快速应用到当前工程。
*   **数据导入向导 (`Ctrl+I`)**: 位于 `File -> Import -> Import from Excel / CSV / DBC...` 或 `Wizards -> Import from Excel / CSV / DBC...`，支持从 Excel 表格、CSV、DBC (CAN 通信矩阵) 文件批量导入生成 AUTOSAR 容器与信号配置。

---

## 8. AI 智能助手 (AI Assistant)

### 8.1 配置 API Key
使用 AI 功能需配置 Google Gemini API Key：
1. 环境变量配置：`export GEMINI_API_KEY="your-api-key"`
2. 或在软件界面中打开 `View -> AI Assistant` (Ctrl+Shift+A)，点击面板右上角 **Settings** 填入并保存（安全保存于操作系统 Keychain 中）。

### 8.2 功能说明
*   **自然语言问答**: 针对 AUTOSAR 规范、参数含义及硬件配置疑问进行对话解答。
*   **参数建议与诊断**: 点击参数旁的 AI 建议按钮，结合当前工程上下文提供推荐配置。
*   **文档知识库 RAG**: 自动索引技术规范（支持 Markdown、PDF、文本），提供准确的知识检索。

---

## 9. 界面布局结构

主窗口采用类 Vector DaVinci Configurator 的左侧功能导航栏布局（可通过 `View -> Navigation Bar` 显示或隐藏）：
*   **左侧导航栏 (`Navigation Bar`)**：支持在 **🏠 首页 (`Home`)**（最近项目、工程总览、4 步工作流与模块卡片）与 **🌳 基础编辑 (`Basic Editor`)**（模块树 + 属性面板）之间切换，并提供 **📡 通信配置**、**⚡ RTE/SchM**、**🧭 内存映射**、**📌 硬件映射**、**✅ 配置验证**（带错误徽章）、**🕸️ 依赖图**、**⚙️ 代码生成**、**📁 工程设置** 与 **❓ 使用手册** 快捷入口。

```
+-------------------------------------------------------------------------+
| File  Edit  View  Generate  Analysis  Wizards  Tools  Help              |
+-------------------------------------------------------------------------+
| [Save] | [Undo] [Redo] | [Copy] [Paste] | [Validate] | [Generate]       |
+--------+------------------+---------------------------------------------+
| [🏠首页] |  Module Tree     |  Configuration Panel (或 Home 总览工作区)   |
| [🌳编辑] |  +-----------+   |  +-------------------------------------+  |
| -------- |  | Adc       |   |  | Container: AdcGeneral               |  |
| [📡通信] |  |  +-Cfg    |   |  | +---------------------------------+ |  |
| [⚡RTE ] |  |  +-Channel|   |  | | AdcDevErrorDetect: true         | |  |
| [🧭Mem ] |  | Can       |   |  | +---------------------------------+ |  |
| [📌HW  ] |  +-----------+   |  +-------------------------------------+  |
| -------- |  +-----------+   |  +-------------------------------------+  |
| [✅验证] |                  +-------------------------------------------+
| [🕸️依赖] |                  |  AI Assistant (Ctrl+Shift+A)              |
| [⚙️生成] |                  +-------------------------------------------+
| [📁设置] +------------------+-------------------------------------------+
| [❓手册] | Problems View / Impact View (Bottom Dock)                    |
+--------+----------------------------------------------------------------+
| Status: Ready | Errors: 0 | Warnings: 0 | Mode: Project                 |
+-------------------------------------------------------------------------+
```

---

*版本: v2.0.0 | 基于 AUTOSAR 4.4.0 标准*
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

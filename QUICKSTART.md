# 快速开始

本文覆盖当前 AUTOSAR BSW 配置工具的有效工作流。

## 1. 准备环境与启动

### 方式一：使用启动脚本（推荐，自动检测环境）

```bash
./start.sh
```

### 方式二：手动配置虚拟环境并启动

首次使用或重建环境：

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
python davinci_main.py
```

日常启动：

```bash
source .venv/bin/activate
python davinci_main.py
```

> **macOS (Apple Silicon M 系列芯片) 提示**：
> 如遇旧 x86_64 虚拟环境报 `bad CPU type in executable`，执行以下命令清理并重建：
> `rm -rf venv .venv && python3 -m venv .venv && source .venv/bin/activate && pip install -r requirements.txt`

## 2. 验证安装

```bash
python -m pytest tests/core/test_observers.py -q
python -m pytest tests/generator -q
openspec validate --all --strict
```

## 3. 创建或导入项目

### 新建项目

1. 菜单 `File -> New Project...` (或 `Ctrl+Shift+N`)
2. 输入项目名称。
3. 选择项目类型（如 `Vector DaVinci` 或 `EB Tresos`）。
4. 选择项目保存目录。
5. 保存后将生成 `.dpa` 工程文件。

### 导入 EB Tresos 工程

1. 菜单 `File -> Import EB Tresos Project...`
2. 选择现有的 EB 工程根目录。
3. 如果检测到多个芯片变体，在弹窗中选择目标芯片。
4. 选择导入后的项目保存目录。
5. 工具会自动扫描并加载模块定义 (`.xdm`/`.epd`)、配置实例 (`.epc`/`.arxml`)、模板与硬件资源。

## 4. 基础配置流程

1. 在左侧项目树中选择模块或容器定义。
2. 右键容器定义，选择 `Add Instance` 添加配置实例。
3. 在右侧配置面板编辑参数和引用（支持数值检查、枚举下拉、智能引用跳转）。
4. 使用 `Edit -> Validate Configuration` (`Ctrl+Shift+V`) 进行配置校验，底部 Problems 面板查看结果。
5. 使用 `File -> Save Project` (`Ctrl+Shift+S`) 保存项目。
6. 使用 `Generate -> Generate Code` (`Ctrl+G`) 生成代码。

## 5. 常用功能入口与快捷键

| 功能分类 | 功能名称 | 菜单/入口 | 快捷键 (Win/Linux) | 快捷键 (macOS) |
|----------|----------|-----------|--------------------|----------------|
| **工程管理** | 新建项目 | `File -> New Project...` | `Ctrl+Shift+N` | `Cmd+Shift+N` |
| | 打开项目 | `File -> Open Project...` | `Ctrl+Shift+O` | `Cmd+Shift+O` |
| | 保存项目 | `File -> Save Project` | `Ctrl+Shift+S` | `Cmd+Shift+S` |
| | 工程属性 | `File -> Project Properties...` | - | - |
| | 变体管理 | `File -> Manage Variants...` | - | - |
| | 添加模块 | `File -> Add Module to Project...` | - | - |
| | 加载推荐值 | `File -> Load Recommended Values...` | - | - |
| **导入导出** | 导入 EB 工程 | `File -> Import -> Import EB Tresos Project...` | - | - |
| | 导入值文件 | `File -> Import -> Import Value File...` | - | - |
| | 导入外部数据表 | `File -> Import -> Import from Excel / CSV / DBC...` | `Ctrl+I` | `Cmd+I` |
| | 导出 EPC 文件 | `File -> Export -> Export EPC Files...` | - | - |
| **编辑校验** | 撤销 (Undo) | `Edit -> Undo` | `Ctrl+Z` | `Cmd+Z` |
| | 重做 (Redo) | `Edit -> Redo` | `Ctrl+Y` / `Ctrl+Shift+Z` | `Cmd+Shift+Z` |
| | 复制容器 | `Edit -> Copy` | `Ctrl+C` | `Cmd+C` |
| | 粘贴容器 | `Edit -> Paste` | `Ctrl+V` | `Cmd+V` |
| | 验证配置 | `Edit -> Validate Configuration` | `Ctrl+Shift+V` | `Cmd+Shift+V` |
| | 加载自定义规则 | `Edit -> Load Custom Rules...` | - | - |
| **代码生成** | 生成代码 | `Generate -> Generate Code` | `Ctrl+G` | `Cmd+G` |
| **依赖分析** | 分析跨模块依赖 | `Analysis -> 🔍 分析跨模块依赖...` | - | - |
| | 验证跨模块依赖 | `Analysis -> ✅ 验证跨模块依赖...` | - | - |
| | 依赖关系图 | `View -> Dependency Graph` | `Ctrl+D` | `Cmd+D` |
| **视图工具** | 智能搜索 | `View -> Search...` | `Ctrl+F` | `Cmd+F` |
| | AI 智能助手 | `View -> AI Assistant` | `Ctrl+Shift+A` | `Cmd+Shift+A` |
| **配置向导** | 快速配置向导 | `Wizards -> Quick Configuration...` | `Ctrl+Q` | `Cmd+Q` |
| | 批量创建向导 | `Wizards -> Batch Create...` | `Ctrl+Shift+B` | `Cmd+Shift+B` |
| | 硬件映射向导 | `Wizards -> Hardware Mapping...` | `Ctrl+Shift+H` | `Cmd+Shift+H` |
| | 应用模板向导 | `Wizards -> Apply Template...` | `Ctrl+T` | `Cmd+T` |
| | 数据导入向导 | `Wizards -> Import from Excel / CSV / DBC...` | `Ctrl+I` | `Cmd+I` |
| **帮助支持** | 使用手册 | `Help -> 使用手册 (User Manual)` | `F1` | `F1` |

## 6. AI 智能辅助

使用 AI 功能前配置 Google Gemini API Key：

```bash
export GEMINI_API_KEY="your-api-key"
python davinci_main.py
```

或在软件界面中打开 `View -> AI Assistant`，点击面板右上角 `Settings` 配置 API Key 并保存。

## 7. 模板与代码生成规则

* 生成器仅使用项目模板目录 (`templates/<ModuleName>/`) 或用户指定的模板目录。
* 没有模板的模块会被安全跳过 (`Skipped`)，**不会**使用可能导致版本不匹配的内置兜底模板。
* 测试模板位于 `tests/fixtures/templates/`，仅供自动化回归测试使用。


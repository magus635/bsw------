# 快速开始

本文只覆盖当前有效工作流。旧文档中出现的 `main.py`、`verify.py`、桌面路径均已废弃。

## 1. 准备环境

```bash
cd /Users/qlwang/Documents/GitHub/bsw------
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
```

如果本机已经有可用的 `venv/`，也可以改用：

```bash
source venv/bin/activate
```

## 2. 启动应用

```bash
python davinci_main.py
```

或使用脚本：

```bash
./start.sh
```

## 3. 验证安装

```bash
python -m pytest tests/core/test_observers.py -q
python -m pytest tests/generator -q
openspec validate --all --strict
```

## 4. 创建或导入项目

### 新建项目

1. 菜单 `File -> New Project...`
2. 输入项目名。
3. 选择 `Vector DaVinci` 或 `EB Tresos` 项目类型。
4. 选择项目目录。
5. 保存后会生成 `.dpa` 项目文件。

### 导入 EB Tresos 工程

1. 菜单 `File -> Import EB Tresos Project...`
2. 选择 EB 工程目录。
3. 如果检测到多个芯片变体，选择目标芯片。
4. 选择导入后的项目保存目录。
5. 工具会扫描定义、配置值、模板和硬件资源。

## 5. 基础配置流程

1. 在项目树中选择模块或容器定义。
2. 右键容器定义，选择 `Add Instance`。
3. 在右侧配置面板编辑参数和引用。
4. 使用 `Edit -> Validate Configuration` 或 `Ctrl+Shift+V` 验证。
5. 使用 `File -> Save Project` 或 `Ctrl+Shift+S` 保存。
6. 使用 `Generate -> Generate Code` 或 `Ctrl+G` 生成代码。

## 6. 常用功能入口

| 功能 | 菜单/入口 | 快捷键 |
|------|-----------|--------|
| 新建项目 | `File -> New Project...` | `Ctrl+Shift+N` |
| 打开项目 | `File -> Open Project...` | `Ctrl+Shift+O` |
| 保存项目 | `File -> Save Project` | `Ctrl+Shift+S` |
| 导入 EB 工程 | `File -> Import EB Tresos Project...` | - |
| 导入值文件 | `File -> Import Value File...` | - |
| 导出 EPC | `File -> Export EPC Files...` | - |
| 验证配置 | `Edit -> Validate Configuration` | `Ctrl+Shift+V` |
| 搜索 | `View -> Search...` | `Ctrl+F` |
| 依赖图 | `View -> Dependency Graph` | `Ctrl+D` |
| AI 助手 | `View -> AI Assistant` | `Ctrl+Shift+A` |
| 快速配置 | `Wizards -> Quick Configuration...` | `Ctrl+Q` |
| 批量创建 | `Wizards -> Batch Create...` | `Ctrl+Shift+B` |
| 硬件映射 | `Wizards -> Hardware Mapping...` | `Ctrl+Shift+H` |
| 应用模板 | `Wizards -> Apply Template...` | `Ctrl+T` |
| 配置导入向导 | `Wizards -> Import Configuration...` | `Ctrl+I` |
| 使用手册 | `Help -> 使用手册` | `F1` |

## 7. AI 功能

设置环境变量：

```bash
export GEMINI_API_KEY="your-api-key"
python davinci_main.py
```

或启动应用后打开 `View -> AI Assistant`，点击面板右上角 `Settings` 配置 API Key。

## 8. 模板与生成

生成器只使用项目模板目录或用户模板目录中的模板。没有模板时模块会被标记为 skipped，不会使用内置默认模板生成代码。

测试模板位于 `tests/fixtures/templates/`，仅用于自动化测试。

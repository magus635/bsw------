# AUTOSAR BSW 图形配置工具

基于 Python 和 PySide6 的 AUTOSAR Classic BSW/MCAL 配置工具。当前主线围绕 EB Tresos 工程导入、ARXML/XDM 配置解析、图形化编辑、验证和 EB 模板代码生成。

## 当前入口

推荐使用项目虚拟环境运行：

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
python davinci_main.py
```

也可以使用启动脚本：

```bash
./start.sh
```

当前没有 `main.py` 或 `verify.py` 入口。旧文档、旧脚本或外部笔记中出现这两个命令时，以本 README 和 `QUICKSTART.md` 为准。

## 主要能力

- 项目工作流：新建/打开 `.dpa` 项目，导入 EB Tresos 工程，保存项目状态。
- 定义和值解析：支持 AUTOSAR ARXML、EB XDM/EPC 相关解析和配置值往返。
- 图形编辑：定义层和实例层树视图、参数面板、Undo/Redo、多选删除、搜索和问题列表。
- 验证分析：参数规则、引用规则、跨模块依赖、影响分析和依赖图。
- 代码生成：EB Tresos 风格模板引擎，支持 `[!IF]`、`[!LOOP]`、`[!SELECT]`、宏、XPath、`node:*`、`ecu:*` 等函数。
- 硬件资源：芯片资源、`.properties` 解析、THA 系列示例数据和映射规则。
- 辅助导入：CSV、Excel、DBC 导入向导。
- AI 辅助：Gemini 驱动的问答、配置建议、依赖分析和知识库文档读取。

## 模板机制

生成器不再使用内置默认模板。模板只从项目模板目录和用户模板目录解析；没有匹配模板时模块会被跳过，而不是生成可能不匹配供应商/芯片版本的默认代码。

模板目录通常按模块组织，例如：

```text
templates/
└── Can/
    ├── Can_Cfg.h.tpl
    └── Can_PBcfg.c
```

测试 fixture 位于 `tests/fixtures/templates/`，仅用于测试，不是运行时默认模板库。

## 项目结构

```text
autosar_configurator/
├── core/
│   ├── model/          # 定义层和配置层模型
│   ├── parser/         # ARXML/XDM 解析
│   ├── serializer/     # ARXML/ECUC 序列化
│   ├── rules/          # 验证规则
│   ├── analysis/       # 影响分析
│   ├── ai/             # Gemini、RAG 和提示词上下文
│   ├── hardware/       # 芯片资源、properties、映射规则
│   └── importers/      # CSV/Excel/DBC 导入
├── generator/
│   ├── eb/             # EB 模板词法、渲染、XPath、内置函数
│   ├── generator.py    # 代码生成编排
│   └── template_engine.py
├── ui/
│   ├── davinci_main_window.py
│   ├── controllers/    # 项目、编辑、验证、生成、导航、AI 等控制器
│   ├── widgets/        # 树、配置面板、搜索、问题视图、依赖图
│   ├── wizards/        # 快速配置、批量创建、硬件映射、模板、导入
│   └── dialogs/
├── data/
│   ├── chips/          # 示例芯片定义
│   └── mapping_rules/  # 硬件映射规则
└── utils/
```

## 新项目的结构与必需部分（Format 8）

本工具当前的推荐工程格式是 Format 8。它的核心思想不是“把所有东西都塞进一个目录”，而是把每个模块都做成一个可扫描的模块包，项目根目录只保留工程描述和全局数据。

```text
<project>/
├── project.dpa                 # 工程文件，保存 format_version、module_libraries、module_entries
├── modules/                    # 模块库根目录，按模块组织
│   ├── Mcu/
│   │   ├── module.json         # 模块包描述文件（必需）
│   │   ├── config/
│   │   │   ├── Mcu.xdm         # 模块定义/配置文件
│   │   │   └── McuPreConfiguration.xdm
│   │   ├── templates/
│   │   └── resource/
│   ├── Os/
│   │   ├── module.json
│   │   ├── config/
│   │   ├── templates/
│   │   └── resource/
│   └── ...
├── chips/                      # 芯片资源、YAML/属性文件（可选但推荐）
├── templates/                  # 工程级模板覆盖层（可选）
├── system/                     # 工程级系统描述/集成数据（可选）
├── integration/                # 集成输出目录（可选）
├── base/                       # 基线快照目录（由工具维护）
├── .history/                   # 导入/保存记录（由工具维护）
└── ...
```

### 每一部分的职责

- `.dpa`：工程主文件，保存项目元数据、选择的芯片、模块库、模块列表和基线状态。
- `modules/`：模块库根目录，每个模块必须具备独立包目录。
- `module.json`：模块包的清单文件。它决定这个模块能否被扫描、定义路径是否正确、模板和资源目录在哪、以及哪些文件在什么芯片下生效。
- `config/`：模块配置文件，通常包含定义文件、递归值文件、预配置文件、芯片条件文件。
- `templates/`：该模块的生成模板目录。
- `resource/`：资源文件、属性文件和其他与模块相关的非模板资源。
- `chips/`：芯片资源定义，项目打开和模块加载时用来解析当前芯片的可用配置。

### 典型的 `module.json`

```json
{
  "schema": 1,
  "module": "Os",
  "definition": "/THA6_ASR21/Os",
  "files": [
    { "path": "config/Os_Config.arxml", "chips": ["THA6206_LFBGA292"] },
    { "path": "config/Os_Arti.arxml", "chips": ["THA6206_LFBGA292"] }
  ],
  "pre": [],
  "rec": [],
  "templates": "templates",
  "resources": "resource",
  "implementation": null,
  "origin": { "source": "legacy-t1", "kind": "manual-package" },
  "inferred": true
}
```

### `module.json` 中每一项的含义

| 字段 | 作用 | 影响 |
| --- | --- | --- |
| `schema` | manifest 版本号，当前必须为 `1` | 代码要求它必须是 `1`，否则拒绝加载 |
| `module` | 模块短名，如 `Os`、`Mcu`、`Can` | 作为项目中的模块键，决定模块在工程中如何命名 |
| `definition` | AUTOSAR 定义路径，如 `/THA6_ASR21/Os` | 决定模块的真实 ECUC 定义，必须和 ARXML 中的定义一致 |
| `files` | 包含的配置文件列表，可按芯片条件过滤 | 由扫描器匹配当前芯片，并决定哪个文件包含该模块定义 |
| `pre` | PRE 配置路径列表 | 影响预配置值的加载和基线合并 |
| `rec` | REC 配置路径列表 | 影响推荐值加载和基线生成 |
| `templates` | 模板目录 | 告诉生成器在哪里找模板 |
| `resources` | 资源目录 | 告诉工具在哪里找资源文件 |
| `implementation` | 可选实现目录 | 用于实现层信息，通常为 `null` |
| `origin` | 来源描述（legacy、eb-import、manual-package 等） | 便于维护和追踪模块来源 |
| `inferred` | 是否由扫描器/插件 AST 推断生成 | 用于区分自动推断与手工维护 |

### 兼容性说明

- 旧工程（Format <= 7）可以继续打开，不会被强制重写成新格式。
- 新工程应按 Format 8 模式建立，并提供 `modules/` 和 `module.json` 结构。
- 只有满足 `module.json` + `definition` + `files` 约束的模块包，才能被 `scan_library()` 和 `WorkspaceProject.add_module_from_package()` 正确识别。

## 运行测试

激活虚拟环境：

```bash
source .venv/bin/activate
```

> **提示**：如需新建干净环境或解决 macOS Apple Silicon 下旧 `venv` 的 `bad CPU type` 报错，可执行：
> `rm -rf venv .venv && python3 -m venv .venv && source .venv/bin/activate && pip install -r requirements.txt`

常用验证命令：

```bash
python -m pytest tests/core/test_observers.py -q
python -m pytest tests/generator -q
openspec validate --all --strict
```

完整测试集包含 UI、AI、真实工程兼容和生成器场景。涉及外部 API 或真实 EB 工程的测试应默认 mock 或显式配置环境后再运行。

## AI 配置

AI 功能使用 Google Gemini API Key。可用两种方式配置：

```bash
export GEMINI_API_KEY="your-api-key"
python davinci_main.py
```

或在应用中打开 `View -> AI Assistant`，点击 AI 面板右上角 `Settings` 配置。API Key 优先存入系统 keychain；不可用时回退到 QSettings。

## 文档索引

- `QUICKSTART.md`：第一次启动和基础工作流。
- `HOW_TO_RUN.md`：运行、测试、虚拟环境和调试命令。
- `DEBUG_GUIDE.md`：常见排障和开发调试。
- `PROJECT_SUMMARY.md`：当前代码架构概览。
- `doc/XPath语言参考.md`：模板 XPath 和函数参考。
- `doc/EB_Tresos_XDM格式解析说明.md`：EB XDM/EPC 相关说明。
- `doc/DBC文件导入使用说明.md`：DBC 导入说明。
- `doc/Hardware_Mapping硬件映射使用说明.md`：硬件映射说明。

过期的日期型审查报告、方案草案和一次性调试产物已从仓库移除。

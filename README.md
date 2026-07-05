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

## 运行测试

默认先激活虚拟环境：

```bash
source .venv/bin/activate
```

如果仓库已有旧的 `venv/`，也可以使用：

```bash
source venv/bin/activate
```

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

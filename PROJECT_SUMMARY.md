# 项目当前概览

本文描述当前代码形态，替代早期 “MainWindow + TreeView + ConfigPanel” 阶段总结。

## 目标

本项目是 AUTOSAR Classic BSW/MCAL 图形配置工具，重点能力包括：

- 导入 EB Tresos 工程。
- 解析 AUTOSAR ARXML、EB XDM/EPC 配置。
- 编辑模块定义和值实例。
- 校验参数、引用和跨模块依赖。
- 使用 EB Tresos 风格模板生成 C 配置代码。
- 管理芯片硬件资源、模板、导入向导和 AI 辅助。

## 当前入口

```bash
python davinci_main.py
```

主窗口类：

```text
autosar_configurator/ui/davinci_main_window.py
```

旧入口 `main.py` 不存在，不再维护。

## 主要架构

```text
autosar_configurator/
├── core/
│   ├── model/          # 基础模型、ECUC 定义和值模型
│   ├── parser/         # ARXML、ECUC 定义、XDM 配置解析
│   ├── serializer/     # ARXML/ECUC 序列化
│   ├── rules/          # 结构、引用、依赖和自定义验证规则
│   ├── analysis/       # 影响分析
│   ├── importers/      # CSV、Excel、DBC 导入器
│   ├── hardware/       # 芯片资源、properties、XDM 提取、映射规则
│   ├── ai/             # Gemini、RAG、提示词、依赖分析
│   ├── config_manager.py
│   └── workspace_manager.py
├── generator/
│   ├── generator.py
│   ├── template_engine.py
│   ├── eb_template_engine.py
│   └── eb/
├── ui/
│   ├── davinci_main_window.py
│   ├── controllers/
│   ├── widgets/
│   ├── wizards/
│   └── dialogs/
├── data/
│   ├── chips/
│   └── mapping_rules/
└── utils/
```

## UI 分层

`DaVinciMainWindow` 负责窗口组装和共享状态。具体行为拆分到控制器：

- `ProjectController`：新建、打开、保存、EB 导入、模块添加、最近文件。
- `EditController`：参数修改、容器创建/删除/移动/重命名、复制粘贴、Undo/Redo。
- `ValidationController`：验证和自定义规则加载。
- `GenerationController`：模板发现、异步生成和生成状态汇总。
- `NavigationController`：搜索、跳转和引用导航。
- `DependencyGraphController`：依赖图和 AI 辅助依赖分析。
- `AiAssistantController`：AI 面板、异步问答和参数建议。
- `WizardController`：快速配置、批量创建、硬件映射、模板和导入向导。

## 模板和代码生成

生成器当前原则：

- 只从项目模板目录和用户模板目录查找模板。
- 没有模板时跳过该模块，不使用内置默认模板。
- 支持 EB Tresos 语法和标准模板两种渲染路径。
- 支持 variant、跨模块上下文、ECU resource 和 `.properties` 资源查询。

关键文件：

```text
autosar_configurator/generator/generator.py
autosar_configurator/generator/eb_template_engine.py
autosar_configurator/generator/eb/
```

测试 fixture：

```text
tests/fixtures/templates/
```

## 项目与持久化

项目保存为 `.dpa` 文件。`WorkspaceManager` 负责项目创建、保存、加载、EB 工程导入、芯片选择、模块管理和路径重映射。

关键文件：

```text
autosar_configurator/core/workspace_manager.py
autosar_configurator/core/config_manager.py
```

## 硬件资源

硬件资源支持：

- THA 系列 YAML 示例芯片。
- EB `.properties` 解析。
- XDM 芯片资源提取。
- 通用资源映射和 legacy mapper 兼容层。
- UI 硬件映射向导。

关键目录：

```text
autosar_configurator/core/hardware/
autosar_configurator/data/chips/
autosar_configurator/data/mapping_rules/
```

## 导入能力

当前导入路径：

- EB Tresos 工程导入：`File -> Import EB Tresos Project...`
- 单模块值文件导入：`File -> Import Value File...`
- 配置数据导入向导：`Wizards -> Import Configuration...`
- CSV、Excel、DBC 导入器：`autosar_configurator/core/importers/`

## AI 能力

AI 功能使用 Gemini：

- AI Assistant 面板问答。
- 参数配置建议。
- 跨模块依赖分析。
- 文档知识库读取，支持文本、Markdown、PDF 和图片。

API Key 配置方式：

```bash
export GEMINI_API_KEY="your-api-key"
```

或在应用中打开 `View -> AI Assistant`，点击面板 `Settings`。

## 推荐验证

```bash
python -m pytest tests/core/test_observers.py -q
python -m pytest tests/generator -q
openspec validate --all --strict
```

UI 测试建议：

```bash
QT_QPA_PLATFORM=offscreen python -m pytest tests/ui -q
```

默认回归不要依赖外部网络或用户本机 EB 工程路径。需要真实 EB 工程的验证应显式配置路径并单独运行。

## 文档维护规则

- `README.md` 是项目事实入口。
- `QUICKSTART.md` 是第一次使用入口。
- `HOW_TO_RUN.md` 是命令入口。
- `DEBUG_GUIDE.md` 是排障入口。
- 过期的日期型审查报告、方案草案和一次性调试产物不再保留在仓库中。

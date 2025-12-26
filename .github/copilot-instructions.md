# AI Agent 使用说明（针对此代码库的要点）

目的：让 AI 编码助手能快速上手本仓库，包含架构、关键工作流、项目约定与集成点。

- **大体架构**: 三层分工：UI 层（autosar_configurator/ui）负责交互与 undo/redo；核心层（autosar_configurator/core）实现数据模型、解析/序列化、配置管理与工作区管理；生成层（autosar_configurator/generator）负责 EB Tresos 兼容模板渲染与代码输出。

- **关键入口**: 启动程序为 [main.py](main.py)（GUI），也可使用 [start.sh](start.sh) 启动并自动安装依赖。

- **常用命令**:
  - 启动应用: `./start.sh` 或 `python3 main.py`（参见 [QUICKSTART.md](QUICKSTART.md)）
  - 安装依赖: `./install_deps.sh` 或 `pip install -r requirements.txt`（参见 [HOW_TO_RUN.md](HOW_TO_RUN.md)）
  - 运行单测: `python3 -m pytest tests/core/test_observers.py -v`，全部测试: `python3 -m pytest tests/ -v`
  - 验证脚本: `python3 verify.py`

- **项目特有约定 / 模式**:
  - “项目类型”检测：通过 `autosar_configurator/core/config_manager.py:ProjectTypeDetector` 判断 Vector vs EB Tresos，可能依赖环境变量 `TRESOS_PLUGINS_PATH`。
  - 配置管理中心：`WorkspaceManager` + `WorkspaceProject` 管理多个模块；每个模块对应 `ConfigurationManager`（见 [autosar_configurator/core/config_manager.py](autosar_configurator/core/config_manager.py)）。
  - 引用解析：采用 EMF 风格（字符串路径转对象指针），在 `WorkspaceProject.resolve_all_references()` 中完成，生成反向引用索引以支持“谁引用我？”查询。
  - 代码生成路由：参数按 `PRE-COMPILE` / `LINK-TIME` / `POST-BUILD` 分类（见 `ConfigClass` 与 [autosar_configurator/generator/generator.py](autosar_configurator/generator/generator.py)）；生成器会写入 `.{ModuleName}.meta` 指纹文件以跳过重复生成。
  - 模板引擎：EB Tresos 兼容模板，引擎位于 `autosar_configurator/generator/eb_template_engine.py`（严格/非严格模式影响渲染错误处理）。

- **集成点 & 外部依赖**:
  - GUI: PySide6（在 requirements.txt 中声明）
  - XML: lxml 用于 ARXML 解析/序列化（查看 `autosar_configurator/core/parser` 与 `autosar_configurator/core/serializer`）
  - EB Tresos 插件路径：由 `TRESOS_PLUGINS_PATH` 环境变量影响 `ConfigLoader.get_def_search_paths()` 的搜索路径。

- **开发/调试提示（给 AI 的具体建议）**:
  - 修改模型/序列化相关代码时，优先运行 `python3 -m pytest tests/core/test_parser_serializer.py -q`。
  - 若修改生成模板，注意 `CodeGenerator._calculate_fingerprint()` 的稳定性（排序/遍历策略会影响 hash）。
  - GUI 相关改动请在本地带显示器环境下跑（远程 SSH 无法显示窗口）；可通过 `python3 -m pytest tests/ui/test_ai_ui.py -q` 检查部分 UI 集成测试。

- **代码风格与不成文约定**:
  - 在生成器与配置管理中大量依赖“确定性排序”（sorted by name）来保证可重复输出——避免在这些路径引入未排序的集合遍历。
  - 对外路径引用与存盘采用相对项目根/项目文件夹约定（见 `WorkspaceManager.save_project()` 的写法）。

- **重要文件速览（优先阅读）**
  - [README.md](README.md) — 项目总览
  - [QUICKSTART.md](QUICKSTART.md) / [HOW_TO_RUN.md](HOW_TO_RUN.md) — 启动与调试流程
  - [main.py](main.py) — 程序入口
  - [autosar_configurator/core/config_manager.py](autosar_configurator/core/config_manager.py) — 配置管理、項目类型检测、DEF/REC 扫描
  - [autosar_configurator/core/workspace_manager.py](autosar_configurator/core/workspace_manager.py) — WorkspaceProject/项目加载与引用解析
  - [autosar_configurator/generator/generator.py](autosar_configurator/generator/generator.py) — 代码生成主流程与模板路由
  - [autosar_configurator/ui/main_window.py](autosar_configurator/ui/main_window.py) — UI 主要交互和命令绑定（undo/redo via CommandManager）

- **不要做的事（AI 约束）**:
  - 不要改变生成器的排序或遍历順序以“优化”性能，除非同时保留或更新指纹/排序逻辑并补充测试。
  - 不要在没有本地 GUI 环境的情况下运行 UI 相关手工验证。

请审阅此文档并指出需要补充的部分（例如更详细的函数级示例、推荐的 VS Code launch 配置或 CI 步骤）。

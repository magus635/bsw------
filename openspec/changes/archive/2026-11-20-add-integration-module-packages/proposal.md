# Add Integration Module Packages (Phase 1)

## Why

设计方案 `docs/superpowers/specs/2026-11-09-integration-module-package-design.md` §3 列出的痛点：

- **P1** 模块没有“包”的概念：每个模块只记一个 `def_path`，pre、rec、模板、资源靠文件名或目录约定去猜，关系断了不报错。
- **P2** Pre 值没有进入工程的通道：EB 的 `McuPreConfiguration.xdm` 导入时被跳过；Vector `_pre.arxml` 只能经 “Load Recommended Values” 与 Rec 混在一起手动加载，可随意修改、不再重新应用。
- **P3** 值没有来源信息：只有 `is_modified`，分不出 Default、Pre、Rec 和用户值。
- **P4** 工程目录名在 20 多处写死，生成器往上找 `Def` 来猜工程根。
- **P5** 模板被复制两份，每次保存都用插件原件静默覆盖 `templates/<Module>/`。
- **P6** link 模式依赖符号链接，在 Windows 上不可靠。
- **P7** Vector 组件的定义与 pre 分散在多个目录（本阶段只准备包内按路径合并，入库工具在阶段 3）。
- **P8** 删除模块无法找回，`modules` 兼任激活清单和文件位置表（本阶段把 `modules` 改为按定义路径登记的激活清单；删除归档在阶段 2）。
- **P9** 工程目录结构不清晰：出厂资料与工程自有内容混放，没有报告和归档的位置。

## What Changes

本提案只覆盖设计方案的**阶段 1**：W1、W2、W4、W6、W9（§9）。

- **W1 工程目录表**：`.dpa` format 8 新增 `directories`、`module_libraries`；工程根一律取 `.dpa` 所在目录；写死的目录名集中到一个解析模块，旧格式的默认值表除外。format ≤7 的工程按原逻辑打开，保存时仍写 7。
- **W2 模块包**：`module.json` 清单 + `config/` 目录（define、pre、rec 同目录）；文件只是来源，角色按 AUTOSAR 路径判定；文件级芯片条件；包内按 AUTOSAR 路径合并，冲突报错；没有清单时从 EB `plugin.xml` 推断（`autosar/*.arxml` 不加载）；模块库扫描与按定义路径定位。
- **W4 基线层**：分层基线 DEFAULT < REC < DERIVED < PRE（阶段 1 DERIVED 为空，但接口与合并都支持）；基线快照 `config/base/<Module>.arxml`，哈希记在 `.dpa`；三方合并从不删除，改动前先预演、经确认才写入；值来源由比较得出；Pre 只读锁定在命令层执行，可按参数解除锁定（`pre_unlocked`）；添加模块时默认用 Rec 初始化。
- **W6 模板查找**：`templates/<Module>/`（工程覆盖层）→ 包内模板目录；format 8 不再在保存时复制模板；生成器指纹只按模板内容计算。
- **W9 EB 工程导入**：生成 format 8 工程，插件目录登记为模块库，不再复制模板、不再创建符号链接，`PreConfiguration` 按基线层处理而不是跳过。

不在本提案内：可用模块对话框（W3）、REC 新建容器初值（W5）、删除归档（W7）、旧工程升级命令（W8）、IMPL 查询接口（W10）、Vector SIP 入库（W11）、DaVinci 工程导入（W12）。

## Impact

- Affected specs：
  - `module-packages`（新能力，ADDED）
  - `config-baseline`（新能力，ADDED）
  - `project-file`（只存在于未归档的 `add-eb-import-modes` 中，按 ADDED 处理：format 8 目录表、模块库、旧格式兼容、EB 导入）
  - `code-generation`（只存在于未归档的 `remove-default-templates` 中，按 ADDED 处理：模板查找顺序“覆盖层 → 包”）
- Affected code（详见 tasks.md）：
  - 新增 `autosar_configurator/core/project_paths.py`、`core/packages/`、`core/baseline/`、`tools/compare_generation.py`
  - 修改 `core/workspace_manager.py`、`core/config_manager.py`、`core/parser/xdm_config_parser.py`、`generator/generator.py`、`ui/commands.py`、`ui/controllers/*`、`ui/widgets/davinci_config_panel.py` 等
- 兼容性：format ≤7 的工程打开、保存、生成结果均不变（不应用 PRE）；EB 插件目录不需要改造即可作为模块包。

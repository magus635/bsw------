# 重构计划：P2-6（God Object）/ P2-7（双重 ECUC 定义模型）

状态：草案（待评审，未开工）
适用代码：`autosar_configurator/`
前置条件：**先恢复可运行的 pytest 测试套件**（当前本机三个解释器均无 pytest）。没有绿色基线，这两项重构都不应开工。

---

## 0. 共同的硬约束（两项都适用）

1. **行为零变化**：纯结构重构。生成器输出指纹（`CodeGenerator._calculate_fingerprint()`）必须逐字节稳定。每个阶段后跑 `verify_fingerprints.py`（若存在）+ 黄金主测试 `tests/generator/eb/test_golden_master.py`。
2. **测试先行**：每抽取一个单元，先为其当前公开行为补特征测试（characterization tests），再搬代码。
3. **小步提交**：每个阶段一个可独立回滚的 commit；每步后整套 `pytest tests/` 必须保持绿色。
4. **确定性顺序**：不改动任何 `sorted()` 遍历/序列化顺序（CLAUDE.md 既定约定）。
5. **入口双轨**：`davinci_main.py`(推荐) 与 `main.py`(legacy) 当前并存——见 P2-7 第 1 步，需先决策 legacy 入口去留。

---

## P2-6 — 拆分 `DaVinciMainWindow`（God Object）

### 现状（实测）
- `ui/davinci_main_window.py` ≈ **3809 行**，单个 `DaVinciMainWindow` 类挂 **~88 个方法**、**71 处 `.connect()`** 信号接线。
- 一个类同时负责：UI 搭建、项目 I/O、模型编辑命令、验证、代码生成、AI 助手、向导、依赖图/影响分析、搜索导航、选择/上下文同步。
- 持有的协作者（`__init__`）：`workspace_manager`、`def_parser`、`undo_stack`、`chip_constraint_service`、`config_manager`、`current_project`、`thread_pool`、`settings`、以及各 widget（`tree_view`/`config_panel`/`dep_graph_*`/`ai_assistant_*`/`search_widget`）。

### 目标架构
保持 `DaVinciMainWindow` 为**瘦壳（thin shell）**：只负责创建 widget、布局、把信号转发给 controller。业务逻辑迁入 **controller 协作对象**，按职责切分。不引入框架，纯组合（composition + delegation）。

```
DaVinciMainWindow (壳: 菜单/工具栏/dock/信号转发)
├── ProjectController        项目/单模块 I/O、最近文件、会话、closeEvent 脏检查
├── EditController           参数/容器 CRUD、rename/move、copy/paste、undo 接线
├── ValidationController     validate、custom rules、跨模块依赖校验、Problems 视图
├── GenerationController     generate_code / single / project、收集配置
├── AiAssistantController    AIWorker、配置、消息、help（含 P2-9 子进程逻辑）
├── WizardController         各 launch_*_wizard 与 _on_*_completed
├── NavigationController     search、navigate_to_*、definition info、impact、reverse refs
└── DependencyGraphController dep graph 分析与展示
```

每个 controller 构造时注入它需要的协作者（`workspace_manager`、`undo_stack`、当前 `config_manager` 提供者等），**不反向持有整窗**——窗口通过回调/Qt 信号接收 controller 的结果（如"跳转到路径""刷新树""显示状态栏消息"），避免 controller↔window 双向强耦合。

### 分阶段（每阶段独立 PR，可回滚）
> 抽取顺序按"依赖最少、边界最清晰"优先，先摘掉外围，最后动核心编辑/选择同步。

1. **阶段 0｜安全网**：为 `DaVinciMainWindow` 关键流程补集成测试（`tests/ui/` 已有 `test_davinci_integration.py`、`test_undo_commands.py`、`test_reference_error_display.py` 可作基线）。补齐：项目打开→编辑→保存、生成、验证、closeEvent 脏检查（含本轮 P2-10 新增的单模块分支）这几条主路径的端到端断言。**UI 测试需显示环境**，CI 用 `pytest-qt` + offscreen（`QT_QPA_PLATFORM=offscreen`）。
2. **阶段 1｜AiAssistantController**：最独立、外部依赖明确（Gemini/子进程），且本身是 P2-8/9 的载体。把 `AIWorker`/`AIWorkerSignals` + `_setup_ai_assistant`/`_configure_ai_settings`/`_handle_ai_*`/`_on_ai_*`/`_on_ai_help_requested` 整体迁出。顺带承接 P2-8 的 secret-store 改造点。
3. **阶段 2｜WizardController**：`launch_*_wizard` 与 `_on_*_wizard_completed`——纯触发+回调，几乎无共享状态。
4. **阶段 3｜DependencyGraphController + NavigationController**：依赖图分析/展示、搜索、`_navigate_to_*`、impact、reverse references、Problems 视图触发。这些是"读"路径，风险低。
5. **阶段 4｜GenerationController**：`generate_code`/`_generate_single_module_code`/`_generate_project_code`/`_get_all_project_configurations`。生成路径**必须**配指纹回归。
6. **阶段 5｜ValidationController**：`validate_configuration`/`load_custom_rules`/`_validate_cross_module_dependencies`/Problems 视图。
7. **阶段 6｜ProjectController**：`new/open/save_project`、`_load_project_at_path`、`import_eb_project`、`_save_configuration`、最近文件、`_auto_load_last_project`、`_load_last_session`、`closeEvent` 脏检查。
8. **阶段 7｜EditController（最后）**：`handle_parameter_change`、容器 CRUD、`handle_move/rename_container`、copy/paste、`_on_undo_clean_changed`、选择/上下文同步（`_on_instance_selected`/`_on_def_selected`/`_update_active_context`/`_on_parameter_changed`）。这是与树/面板信号纠缠最深的部分，放最后。

### 退出标准
- `DaVinciMainWindow` 降到 ~600–900 行（仅壳层）。
- 每个 controller < ~500 行、单一职责、可单测（不必拉起整窗）。
- 全套测试绿；生成指纹零变化。

### 风险与缓解
- **隐式共享状态**（`self.config_manager` 随模式切换、`self.current_project`）：引入一个轻量 `AppContext`/provider（`get_active_config_manager()`），controller 通过它取当前态，而非各自缓存，避免状态分叉。
- **Qt 信号时序**：抽取时保持 `.connect()` 的连接关系不变，只是把槽函数搬家；逐个迁移、每次只动一组信号。

### 估算
~7 个 PR，3809→壳层。中等风险（UI 测试薄是主要风险，故阶段 0 不可省）。

---

## P2-7 — 合并双重 ECUC 定义模型

### 现状（实测）——这是"两套栈"而非单纯两个类
| | 规范栈（推荐 / DaVinci） | 遗留栈（legacy） |
|---|---|---|
| 入口 | `davinci_main.py` → `DaVinciMainWindow` | `main.py` → `MainWindow` |
| 定义模型 | **`definition_model.py`**：`EcucModuleDef`/`EcucContainerDef`/`EcucParameterDef`/`EcucReferenceDef` + `EcucParameterType`/`ConfigClass`/`VariantType` | **`ecuc_model.py`**：`EcucContainer`/`EcucParameter`/`EcucReference`（继承 `container.py` 的 `Container`/`Parameter`/`ArxmlElement`） |
| 值模型 | `configuration_model.py`（`EcucContainerValue`…） | 同左（共用） |
| DEF 解析 | `ecuc_def_parser.py` / `xdm_config_parser.py` | `arxml_parser.py::_parse_ar_package → parse_ecuc_module_def`（产出 `EcucContainer`） |
| UI widget | `davinci_tree_view.py` / `davinci_config_panel.py` | `tree_view.py` / `config_panel.py` |
| 消费者数量 | **~40 个文件**（config_manager、所有 rules、generator、serializer、workspace、全部测试） | **仅 3 个文件**：`arxml_parser.py`、`config_panel.py`、`tree_view.py`（后两者只被 `main_window.py` 引用） |

**结论**：`definition_model` 是事实上的规范模型；`ecuc_model` 是仅服务于 legacy `main.py` 入口的少数派。所谓"契约漂移"来自 `arxml_parser` 里有一条**平行的 def 解析路径**（产出 `EcucContainer`），与 `ecuc_def_parser`（产出 `EcucModuleDef`）并存。

### 关键决策点（必须先定，决定工作量量级）
**`main.py` / `MainWindow`（legacy 入口）还要保留吗？**

- **方案 A（推荐｜退役 legacy）**：若 `main.py` 已无人用（`davinci_main.py` 是 README/CLAUDE.md 钦定入口，且 legacy 栈无任何测试覆盖），则直接退役整条 legacy 栈：
  1. 删除 `main.py`、`ui/main_window.py`、`ui/widgets/config_panel.py`、`ui/widgets/tree_view.py`。
  2. 删除 `arxml_parser.py` 中产出 `EcucContainer` 的 def-side 方法（`parse_ecuc_module_def`/`_parse_ecuc_container_def`/`_parse_ecuc_parameter_def`/`_parse_ar_package` 的 def 分支），**保留** `parse_ecuc_configuration_values`（值侧，规范栈在用）。
  3. 删除 `core/model/ecuc_model.py`；评估 `core/model/container.py` 的 `Parameter`/`Container`/`ArxmlElement` 是否还有其他消费者，无则一并清理。
  4. `definition_model` 成为唯一定义模型。
  - 工作量小、风险低（删除未被测试/未被推荐入口引用的代码），但**需用户确认 legacy 入口确实可弃**。

- **方案 B（保留 legacy）**：把两个 legacy widget 迁移到 `definition_model`，让 `MainWindow` 也用规范模型，再删 `ecuc_model`：
  1. 给 `definition_model` 的类补齐 legacy widget 依赖的访问器（如 `is_required()`/`is_multiple()`/`multiplicity_str()`/`get_reference_def()`——这些目前在 `ecuc_model.EcucContainer` 上）。
  2. 改 `config_panel.py`/`tree_view.py` 的 `isinstance(x, EcucContainer)` 分支为 `EcucContainerDef`。
  3. 让 legacy 入口的 DEF 解析改走 `ecuc_def_parser`，移除 `arxml_parser` 的 def-side 平行路径。
  4. 删除 `ecuc_model.py`。
  - 工作量中等，保留双入口但统一模型。

### 分阶段（方案 A）
1. **决策 & 确认**：与用户确认 `main.py` 去留 → 选 A/B。
2. **特征测试**：为 `arxml_parser.parse_ecuc_configuration_values`（保留项）补/确认测试；记录将删除路径当前是否有任何测试触达（实测：无）。
3. **物理删除 legacy 栈**（方案 A）：按上面 1–3 删文件/方法，跑全套测试 + 生成指纹。
4. **清理**：删 `ecuc_model.py`；检查并清理 `container.py` 孤儿基类；更新 `__init__.py` 导出与 import。
5. **文档**：在 CLAUDE.md 架构段标注"单一定义模型 = `definition_model`，值模型 = `configuration_model`"。

### 退出标准
- 全仓仅剩一套定义模型（`definition_model`）。
- `grep -r "ecuc_model"` 零命中。
- `arxml_parser` 只承担值侧解析；DEF 解析统一在 `ecuc_def_parser`/`xdm_config_parser`。
- 测试绿、指纹零变化。

### 风险与缓解
- **误删仍在用的路径**：删除前用 `grep -rn` + 运行时断点确认 def-side 方法零调用（实测调用点全部在 `arxml_parser.py` 内部自递归，外部仅 legacy `main_window` 链路）。
- **`container.py` 基类被其他模块复用**：删 `ecuc_model` 前单独 grep `from .container import` 的全部消费者，逐一核实。

### 估算
- 方案 A：1–2 个 PR，**低风险**（删除占主导），前提是用户确认 legacy 入口可弃。
- 方案 B：3–4 个 PR，中等风险。

---

## 建议执行顺序
1. **先 P2-7（方案 A）**：它会删掉 legacy `main_window` 等大量代码，缩小 P2-6 的战场（少一套 widget/入口要照顾）。
2. **再 P2-6**：在更干净的单栈上拆 God Object。

## 立即需要用户拍板的两件事
1. `main.py` / `MainWindow` 这条 legacy 入口是否可以**直接退役**？（决定 P2-7 走方案 A 还是 B）
2. 是否同意先 `./install_deps.sh` 恢复 pytest，作为两项重构的绿色基线门禁？

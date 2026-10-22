## Context

芯片在 EB tresos 中由 Resource 模块的 `ResourceSubderivative` 选择，其它模块通过 `ecu:get/ecu:list` 读该芯片的资源。本工具把芯片提升为项目属性 `selected_chip`，资源来自芯片 YAML（`ecu_resources`）与 `.properties`。两套机制并存，加上四个修改入口，导致 `selected_chip`、界面约束、配置中的选择器参数三者可能不一致。芯片 YAML 已有 `selectors`（`Os.OsResourceSubderivative: Os_THA6412`、`Resource.ResourceSubderivative: THA6412_BGA516`），提供了芯片 → 选择器取值的映射。

## Goals / Non-Goals

- Goals:
  - `selected_chip` 为唯一事实来源，所有入口经同一个操作生效。
  - 用户主动选芯片后，选择器参数、ECU 资源、界面约束立即一致。
  - 不在用户不知情时改动已有配置（打开、导入只诊断）。
- Non-Goals:
  - 不改变芯片 YAML 格式与 `selectors` 语义。
  - 不处理 `autosar/*.arxml` 兜底与 ARXML 导出。
  - 不在切换芯片时重新解析已加载的模块定义。

## Decisions

- **Decision: 一个核心方法 `WorkspaceProject.apply_chip_selectors() -> List[SelectorChange]`。**
  对当前芯片 `selectors` 中的每个 `<Module>.<parameter>`：模块未加载则跳过；参数为模块级（`configuration.parameter_values`，如 Os）或容器参数（遍历容器树按名称定位，与 `check_selectors` 相同）时，把所有不等于声明值的实例改为声明值；参数在配置中不存在但其所在容器存在且唯一时，按定义创建并赋值；连所在容器都不存在时（例如刚添加的模块配置为空），若从顶层到该容器的每一级都是单实例容器，则按定义创建这条容器链再赋值；否则记为“未写入”并返回原因。返回值列出 `(key, old, new)`，供界面显示。无界面依赖，便于单测。
  - Alternatives considered: 在 `chip_changed()` 内部直接写入。否决：`chip_changed()` 也在打开项目等非用户选择场景使用，混在一起会导致打开项目时静默改配置。

- **Decision: 写入时机只限“用户主动选芯片”。**
  新建项目向导确认、Project Properties 中芯片改变并按 OK、Project Properties 中点 “Apply Chip Selectors”、以及在已有芯片的项目中添加模块。打开项目和导入 EB 工程只运行 `check_selectors` 并提示。
  - 理由：导入的 EPC 来自 EB，是用户已有的真实配置；若它与所选芯片不一致，更可能是选错了芯片，应由用户判断。

- **Decision: UI 层只有一个入口函数（主窗口/项目控制器中的 `apply_project_chip(chip, write_selectors: bool)`）。**
  依次：设置 `selected_chip` → `chip_changed()` → `chip_constraint_service.set_project/set_chip` → （可选）`apply_chip_selectors()` → `diagnose_ecu_resources()` → 刷新树和配置面板 → 标记未保存。四个入口全部改为调用它。

- **Decision: 选择器参数在配置面板只读；移除 `ResourceSubderivative` 反向切换。**
  双向同步需要从选择器值反查芯片，而 Os 的取值（`Os_THA6412`、`Os_SC300`）与芯片名不是一一对应，反查可能有歧义；单向（芯片 → 参数）更简单且无歧义。

- **Decision: 选择器写入不进入撤销栈。**
  芯片切换本身不可撤销（它还改动 `chips/` 副本、ECU 资源）；把其中的参数写入单独放进撤销栈会让撤销只回退一半。写入后标记未保存；已有撤销记录保存的是各自参数的旧值，不受影响。

- **Decision: 反查只用于兼容旧项目。**
  旧项目没有 `selected_chip` 但配置里有 `ResourceSubderivative` 时，用芯片库中 `selectors` 反查得到芯片（唯一匹配才采用，否则不设置并提示）。

## Risks / Trade-offs

- 用户习惯在 EB 中通过 `ResourceSubderivative` 切换芯片 → 只读提示中明确指出 Project Properties 的位置；“Open Questions” 中保留是否恢复双向同步的选项。
- 切换芯片后，已加载模块定义中的枚举（由 `ecu:list` 计算）不会自动刷新 → 沿用现状；完成后在状态栏提示“重新加载模块以刷新取值范围”。
- 写入时选择器值不在定义的枚举范围内 → `complete-chip-yaml-as-single-source` 已把芯片库声明的值并入枚举；仍不在时，记为“未写入”并提示，不强行写。

## Migration Plan

无数据迁移。已有项目打开后若选择器不一致，会看到警告，可在 Project Properties 中一键修正。回滚即恢复原入口代码，项目文件格式不变。

## Open Questions

- 是否保留“在配置面板改 `ResourceSubderivative` 即切换芯片”的 EB 习惯（反查芯片后走统一入口）？本提案默认**不保留**（只读）。

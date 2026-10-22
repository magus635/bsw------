## Context

ENABLE 条件（`<a:da name="ENABLE" type="XPath">`）已经在生成和 EPC 导出前求值（`add-definition-enable-conditions`）：条件为假的节点从模板数据中移除，`disabled_configuration_objects()` 返回这些配置对象的 `id()`，供 EPC 导出跳过。条件可以读同模块或其他模块的配置值（如 `node:value(./../OsResourceSubderivative)`），也可以读 ECU 资源（`ecu:get`）。芯片切换会同时改变这两类输入：`chip_changed()` 改 ECU 资源（并可能把芯片复制进 `chips/`），`apply_chip_selectors()` 改选择器参数（并可能创建容器）。

## Goals / Non-Goals

- Goals:
  - 用户在切换芯片之前，就能看到选择器参数的变化，以及哪些已配置容器会失效或恢复，并可以取消。
  - 预览与确认后实际生成的结果完全一致。
  - 预览不改动项目的任何状态（配置、`selected_chip`、ECU 资源、`chips/` 目录）。
- Non-Goals:
  - 不删除失效的配置。
  - 不分析模板中按芯片分支的输出。
  - 不检查新芯片下的个数上限和取值范围。

## Decisions

- **Decision: 在副本上模拟，不“先切换再回滚”。**
  `preview_chip_change(project, chip_name)`（`core/hardware/chip_selectors.py`）：
  1. 取目标芯片的定义（项目 `chips/` 优先，其次芯片库，与 `chip_for_project` 的顺序相同，但按给定的芯片名而不是 `selected_chip`）。
  2. 建一个沙盒项目：浅拷贝项目对象，`selected_chip` 设为目标芯片；`module_managers` 中每个模块的管理器浅拷贝，`configuration` 深拷贝。深拷贝时把模块定义放进 memo，使副本共享定义对象而不复制它们。
  3. 在沙盒上调用 `apply_selectors()`，得到模拟的 `SelectorResult`（含需要创建的容器）。
  4. 用 `EcuResourceResolver(...).resolve(沙盒)` 计算目标芯片的 ECU 资源；不调用 `chip_changed()`，因此不会写 `chips/`。
  返回 `ChipChangePreview(chip, selector_result, modules, ecu_resources)`，其中 `modules` 是沙盒的 `{名称: (定义, 配置副本)}`。
  - Alternatives considered: 真正切换后求值，用户取消时回滚。否决：回滚要恢复选择器旧值、删除新建的容器、撤销 `chips/` 中复制的文件，任何一处遗漏都会让“取消”留下改动；副本模拟天然不会改动项目。

- **Decision: 比较当前状态和模拟状态中被禁用的最上层容器路径。**
  UI 控制器调用 `disabled_containers()` 两次：当前项目（当前配置与 ECU 资源）和沙盒（`preview.modules` 与 `preview.ecu_resources`）。将失效 = 模拟 − 当前，将恢复 = 当前 − 模拟。副本与原配置的容器名相同，路径可以直接比较。
  - 只在切换后求值并报告所有被禁用的容器，会混入切换前就已禁用的容器（T1 在 THA6206 下已有 12 个），所以要两次求值。

- **Decision: 只报告最上层容器，按模块和定义分组。**
  一个被禁用的容器，其子容器和参数也一并失效；逐项列出会淹没信息（T1 将失效的对象共 919 个，最上层容器只有 248 个）。对话框显示 “Os: MemorySection ×118, OsMemoryMap ×94, …”，每组可展开查看路径；完整路径列表写入日志（INFO）。
  - 被禁用的单个参数或引用（不是容器）不进入报告：芯片相关的 ENABLE 条件在实际插件中都位于容器或列表上；参数级的条件多与其他参数有关，与芯片切换无关，列出来是噪音。

- **Decision: `disabled_containers` 放在 `generator/eb/enable_conditions.py`。**
  `disabled_containers(modules, ecu_resources) -> list[DisabledContainer]`，`DisabledContainer(module, path, definition)`：在 `disabled_configuration_objects()` 的同一次求值基础上，遍历配置树，找出在禁用集合中、且父容器不在其中的容器，按模块和路径排序。core 层不依赖 generator（与现有 `ProjectController._disabled_items` 的调用方式一致），由 UI 控制器把 core 的预览和 generator 的求值组合起来。

- **Decision: 预览对话框总是显示，确认后走现有的统一入口。**
  Project Properties 中芯片有变化、“Apply Chip Selectors” 被点击时都先预览，即使没有容器失效（此时显示“不会有配置失效”和选择器变化，用户仍可确认或取消）。确认后调用 `apply_project_chip(chip, write_selectors=True)` 或 `apply_chip_selectors()`，不复用沙盒结果，以保证应用的是项目当前状态。取消时芯片不变，Project Properties 的其他字段照常保存。
  - 新建项目向导没有已有配置，打开、导入不切换芯片，添加模块只影响新模块，这些场景都不预览。

- **Decision: 求值失败不阻止切换。**
  模拟或求值抛异常时记录日志，预览中显示“无法检查失效配置（见日志）”，用户仍可确认切换。单个条件无法求值时，沿用现有规则（视为启用并警告）。

## Risks / Trade-offs

- 预览需要深拷贝配置并求值两次，大项目可能需要几秒 → 只在主动切换芯片时执行，显示等待光标。只深拷贝配置，不拷贝定义。
- 深拷贝的配置对象若持有对其他模块配置的引用（已解析的引用目标），副本会连带复制它们 → 这些副本只用于求值，用完即丢；求值按名称和路径进行，不依赖对象身份。实现时以测试确认“预览后项目完全不变”。
- 预览只覆盖 ENABLE 条件，模板里按芯片分支的输出（如 `scatter.scat`）不在其中 → 对话框注明“模板中按芯片分支的输出不在此列”。T1 的情况中，这些模板分支依赖的正是被禁用的同一批容器，预览已足够提示问题。

## Migration Plan

无数据迁移，无文件格式变化。回滚即去掉预览，恢复为直接切换。

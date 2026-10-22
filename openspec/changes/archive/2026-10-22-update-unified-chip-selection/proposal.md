## Why

项目只用一颗芯片（`WorkspaceProject.selected_chip`），但现在有四个入口能改它，彼此只部分同步：

| 入口 | 改 `selected_chip` | 刷新界面约束（`ChipConstraintService.set_chip`） | 写入模块的选择器参数 |
|---|---|---|---|
| 新建项目向导（`project_controller.py:101`） | ✔ | ✔ | ✘ |
| 导入 EB 工程（`workspace_manager.py:1417`） | ✔ | ✘ | ✘（沿用 EPC 中的值） |
| Project Properties（`project_controller.py:410`） | ✔ | ✘ | ✘ |
| 在配置面板改 `Resource.ResourceSubderivative`（`davinci_main_window.py:704`） | ✔（把参数值直接当芯片名） | ✔ | 只改了这一个，`Os.OsResourceSubderivative` 不跟着变 |

结果是同一项目里可能出现三个不一致的“芯片”：`selected_chip`（决定 `ecu:get/ecu:list` 资源和代码生成）、界面约束所用的芯片、配置里的 `ResourceSubderivative` / `OsResourceSubderivative`（模板按它分支，例如 `OsResourceSubderivative = 'Os_SC300'`）。芯片 YAML 的 `selectors` 段已经声明了每颗芯片对应的选择器取值，但只用于诊断（`ecu_resource_diagnostics.check_selectors`），从不写入。

## What Changes

- **`selected_chip` 是唯一事实来源。** 新增一个统一的“应用芯片”操作，所有入口都调用它：设置 `selected_chip` → 重算 ECU 资源（`chip_changed()`）→ 刷新界面约束 → 按芯片 YAML 的 `selectors` 写入各已加载模块的选择器参数 → 重新诊断。
- **用户明确选芯片时自动写入选择器参数。** 新建项目向导和 Project Properties 里改芯片时，`Resource.ResourceSubderivative`、`Os.OsResourceSubderivative` 等按 `selectors` 写入（容器参数和模块级参数都支持）；写入了哪些值会在状态栏/对话框中列出。之后再添加的模块，加载时同样按当前芯片写入其选择器参数。
  - 这改变了 `complete-chip-yaml-as-single-source` 中“只诊断、不改用户配置”的决定，但仅限于**用户主动选芯片**这一动作；打开项目、导入 EB 工程时仍然只诊断不改写（见 design.md）。
- **导入和打开项目时只检查、可一键修正。** 导入 EB 工程或打开项目时，若配置中的选择器取值与 `selected_chip` 声明的不同，给出警告，并提供 “Apply Chip Selectors” 操作（Project Properties 中）把它们改成芯片声明的值。导入时同时刷新界面约束（修复当前遗漏）。
- **选择器参数在配置面板中只读。** 芯片 YAML 声明过的选择器参数在配置面板显示为只读，提示“由项目芯片决定，请在 Project Properties 中修改”。去掉 `davinci_main_window._on_parameter_changed` 中“改 `ResourceSubderivative` 即切换芯片”的反向路径。
- **芯片名与选择器取值不再混用。** 需要由选择器值反查芯片时（例如旧项目没有 `selected_chip`），按芯片库中各芯片 `selectors` 反查，而不是假定参数值就是芯片名。

## Impact

- Affected specs: `project-chip-selection`（新增能力）。与 `complete-chip-yaml-as-single-source`（已实现，未归档）中的 “Chip Selectors Declared In Chip YAML” 相关：其 “Configured selector differs from the chip” 场景（只警告）在打开/导入时仍成立，用户主动选芯片时改为自动写入。
- Affected code:
  - `autosar_configurator/core/workspace_manager.py`：新增 `WorkspaceProject.apply_chip_selectors()`；`chip_changed()` 的调用约定
  - `autosar_configurator/core/hardware/ecu_resource_diagnostics.py`：复用 `_find_parameter_values` 的定位逻辑；`check_selectors` 不变
  - `autosar_configurator/core/hardware/ecu_resource_resolver.py` 或 `chip_database.py`：由选择器值反查芯片
  - `autosar_configurator/ui/controllers/project_controller.py`：新建/导入/打开/Project Properties 统一走“应用芯片”
  - `autosar_configurator/ui/davinci_main_window.py`：移除 `ResourceSubderivative` 反向切换；统一的约束刷新
  - `autosar_configurator/ui/widgets/davinci_config_panel.py`：选择器参数只读
  - `autosar_configurator/ui/dialogs/project_properties_dialog.py`：“Apply Chip Selectors” 按钮与不一致提示
  - 测试：`tests/core/test_chip_selection.py`（新增）、`tests/ui/`
- 兼容性：
  - 已有项目打开时配置不被改动；只有不一致时出现警告。
  - 芯片 YAML 没有 `selectors` 时，选芯片不写任何参数，行为同现在。
  - 代码生成逻辑不变；对于选择器已与芯片一致的项目，生成结果与指纹不变。
- **不在本变更范围内**：
  - `autosar/*.arxml` 兜底读取按芯片选文件、标准 ARXML 导出（另行提案）。
  - 切换芯片后已解析定义的枚举刷新（现有行为，需重新加载模块）。

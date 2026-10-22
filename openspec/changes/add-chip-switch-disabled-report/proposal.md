## Why

切换芯片可能让已有配置悄悄失效。EB 插件的定义里，很多容器带 ENABLE 条件，条件读的是芯片选择器或 ECU 资源；条件为假时，容器的数据还在，但模板和 EPC 导出都看不到它（`add-definition-enable-conditions`）。

T1 项目（`Desktop/prj/t1`）就是例子。它的 `Os.xdm` 里，`MemoryRegion`、`MemoryBlock`、`MemorySection`、`SystemModeStack`、`OsMemoryMap` 只在 `OsResourceSubderivative = 'Os_THA6206'` 时启用。在 Project Properties 里把芯片改为 `THA6412_BGA516` 后：

- 248 个已配置的顶层容器（MemorySection 118、OsMemoryMap 94、MemoryBlock 25、MemoryRegion 10、SystemModeStack 1）不再参与生成；
- `scatter.scat` 生成为空，`Os_memmap.h` 只剩 `#error`，`Os_link_Cfg.h` 没有 `MEM_*` 宏。

目前切换芯片会立即生效，用户事先不知道会有什么影响，事后也只能看到选择器参数改了哪些值，要等到编译或链接失败才会发现配置失效。

## What Changes

- **切换芯片前先预览，确认后才切换。** 在 Project Properties 中改了芯片并按 OK，或点 “Apply Chip Selectors” 时，先显示一个预览对话框，列出这次切换将带来的影响：
  - 选择器参数会改成什么值（原 `SelectorResult` 的内容，从事后提示改为事前预览）；
  - 将失效的已配置容器：切换后被 ENABLE 条件禁用、不再参与生成和导出；
  - 将恢复生效的容器：切换前被禁用、切换后重新启用。
  容器只列每个失效子树的最上层，按模块和容器定义分组计数，并给出路径示例；完整列表写入日志。
  用户选“切换”才真正应用；选“取消”则芯片和配置都保持不变（Project Properties 中的其他修改，如名称、版本，照常保存）。
- **预览不改动项目。** 在副本上模拟：复制选择器所在模块的配置并写入新芯片的选择器值，按新芯片单独计算 ECU 资源，不写 `chips/`、不改 `selected_chip`。
- **失效的配置不删除。** 确认切换后，失效的容器仍保留在项目里（与 EB 一致），切回原芯片后自动恢复。
- **复用现有的 ENABLE 求值。** 使用 `generator/eb/enable_conditions.py` 中与生成器、EPC 导出相同的求值逻辑，保证预览与实际生成结果一致。新增一个函数，返回被禁用的最上层容器（模块、路径、定义名）。

## Impact

- Affected specs: `project-chip-selection`（新增 1 条需求）。
- Affected code:
  - `autosar_configurator/core/hardware/chip_selectors.py`：新增 `preview_chip_change(project, chip_name)`，返回模拟的选择器变化，以及用于求值的配置副本和 ECU 资源
  - `autosar_configurator/generator/eb/enable_conditions.py`：新增 `disabled_containers(modules, ecu_resources)`
  - `autosar_configurator/ui/controllers/project_controller.py`：Project Properties 改芯片、“Apply Chip Selectors” 先预览、确认后再调用 `apply_project_chip` / `apply_chip_selectors`
  - `autosar_configurator/ui/dialogs/chip_change_preview_dialog.py`（新增）：预览对话框
  - `autosar_configurator/ui/dialogs/project_properties_dialog.py`：“Apply Chip Selectors” 经过预览
  - 测试：`tests/core/test_chip_selection.py`（预览不改项目、与实际写入一致）、`tests/generator/`（`disabled_containers`）、`tests/ui/test_unified_chip_selection.py`（确认与取消）
- 兼容性：
  - 确认切换后的结果与现在相同；配置、生成结果和指纹不变。
  - 新建项目向导（还没有配置）、打开项目、导入 EB 工程、添加模块不预览。
  - 预览需要把整个项目加载进模板引擎求值两次（当前状态和模拟状态）。T1 上从加载项目到两次求值总共约 6.6 秒（求值本身没有单独测量）；期间显示等待光标。
- **不在本变更范围内**：
  - 模板中直接按芯片分支的输出（如 `scatter.scat` 整个包在 `[!IF ... = 'Os_THA6206']` 里）：不解析模板，只报告配置层面的 ENABLE 结果。
  - 新芯片下超出个数上限或取值范围的配置（如从 THA6412 切回 THA6206 后 4 个 `ResourceCoreConfig` 超过 2 核上限）：需要按新芯片重新计算定义，另行提案。

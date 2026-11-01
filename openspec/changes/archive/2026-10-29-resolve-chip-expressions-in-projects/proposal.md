## Why

厂商定义（xdm）里很多默认值和最大个数写成芯片表达式，例如：

- `DEFAULT = ecu:get('Wdg.WdgDeviceInitialTimeout')`
- `MAX = num:i(count(ecu:list('Adc.HwUnitId')))`、`MAX = ecu:get('Dma.AllChannelNum')`

解析器只在解析时、并且手里有芯片数据时才算这些表达式（`EcucDefParser(constraints)`）。但：

- **打开或导入工程**走 `WorkspaceManager.def_parser = EcucDefParser()`，没有芯片数据，这些表达式一律算不出来：默认值为空，最大个数为不限。
- **换芯片**只更新主窗口另一个解析器的芯片数据（`davinci_main_window.py:720`），已加载的定义不会重算。

后果（都已在代码里核对）：

1. **生成**：没配置的参数用 `param_def.default_value` 生成（`overlay_engine.py:80`、`generator.py:771`）。默认值为空时，生成结果和 EB Tresos 按芯片默认值生成的不一样。
2. **新建容器**：新容器的参数按默认值初始化（`config_manager.py:367`）。芯片默认值丢了，就退回成第一个枚举值或 0。
3. **最大个数**：添加实例（`config_manager.py:634`）和校验（`structural_rules.py:56`）都看 `upper_multiplicity`。变成不限后，能建出比芯片实际更多的 ADC 单元、DMA 通道等，校验也不报。

实测（厂商 `test_import_project/Def/plugins` 的 xdm，THA6412 芯片数据）：

- 含芯片表达式的默认值 114 个，其中 54 个能算出值；这 54 个在"打开工程"的解析方式下全部为空。
- 含芯片表达式的 `MAX` 41 个，其中 27 个能算出整数；打开工程时全部变成不限。

另外两处解析器问题：

- 顶层 `v:lst` 的 `MAX` 表达式没有保存到 `upper_multiplicity_expr`，事后无法重算（`ecuc_def_parser.py:229`，子容器那一支有保存）。
- 表达式算出的默认值没有按参数类型转换（整数参数可能拿到字符串）。

## What Changes

- **按工程的芯片数据计算定义里的芯片表达式。** 工程每次重算 ECU 资源（`load_ecu_resources`：打开、导入、添加模块、换芯片都会走到）后，用同一份 `project.ecu_resources` 重新计算所有已加载定义里的芯片表达式：
  - 默认值（`default_expr`）：算得出就用它，并按参数类型转换；算不出则为空（与现在一致）。
  - 枚举范围（`range_expr`）：算得出非空列表就作为选项。
  - 最大个数（`upper_multiplicity_expr`）：算得出正整数就作为上限；算不出则为不限（与现在一致）。
- 解析器把顶层 `v:lst` 的 `MAX` 表达式也保存下来，并保留静态默认值，以便表达式算不出时退回。
- **已有配置值一律不改。** 只影响定义：没配置的参数的生成值、新建容器的初始值、添加实例的上限、多重性校验。
- 表达式求值仍只支持现有的几种形式（`ecu:get`、`ecu:list`、`ecu:list(...)[N]`、`num:i(count(ecu:list(...)))`），外层多余括号去掉后再匹配。更复杂的表达式（`node:when`、`text:concat`、两个 `ecu:get` 相乘等）不在本次范围。

## Impact

- Affected specs：`definition-chip-expressions`（新增）
- Affected code：
  - `core/parser/ecuc_def_parser.py`（保存顶层 `MAX` 表达式和静态默认值）
  - `core/parser/xdm_expression_resolver.py`（去外层括号）
  - 新增一个按资源重算定义的函数，在 `WorkspaceProject.load_ecu_resources` 末尾调用
- **兼容性：生成结果可能变化。** 已有工程中没配置、而定义默认值来自芯片的参数，生成值会从"空/兜底值"变成芯片默认值，更接近 EB Tresos。实施时在厂商示例工程上对比改动前后的生成结果并列出差异，给你确认后再提交。
- **不在本变更范围内**：复杂范围/默认/最大个数表达式；生成前自动校验。

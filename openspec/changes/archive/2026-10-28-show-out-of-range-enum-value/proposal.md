## Why

配置面板里的枚举参数用下拉框编辑。参数当前存的值如果不在下拉框的选项里，`QComboBox.setCurrentText` 不起作用，下拉框显示的是第一项：参数可选时是"(未配置)"，必选时是第一个选项。存的值本身没变，但用户看到的和实际存的不一致。

实测（`fix-port-pin-mode-mapping` 的后续核对）：厂商 Port 定义里 `PortPinMode` 只有 `PORT_PIN_MODE_ALL`，一个存着 `PORT_PIN_MODE_GPIO` 的旧配置，校验报
`Value 'PORT_PIN_MODE_GPIO' is not in allowed literals: ['PORT_PIN_MODE_ALL']`，而点开这个参数，下拉框显示"(未配置)"，和报错对不上。

选项被芯片约束过滤掉时（`_get_allowed_literals`）是同一种情况。

## What Changes

- 枚举下拉框遇到不在选项里的当前值时，加一项显示这个值并选中，文字带"不在可选范围"的标记，提示里列出可选值。
- 这一项只用来如实显示：选中它写回的仍是原值，不会把带标记的文字写进配置。
- 值在选项里，或者没有值时，行为不变。

## Impact

- Affected specs：`config-editor`（新增）
- Affected code：`autosar_configurator/ui/widgets/davinci_config_panel.py` 的 `_create_single_value_editor` 枚举分支；`ListEditorWidget` 复用同一个函数，同样受益。
- 兼容性：只影响值不在选项里的枚举参数的显示；存的值、校验、生成都不变。
- **不在本变更范围内**：
  - 厂商定义里"不可编辑"的参数在界面里仍可改（解析器没有解析该属性）；
  - 自动把旧值迁移成合法值；
  - 其他类型（整数、字符串）的显示。

## Why

Port 的硬件映射规则 `port.yaml` 给每个引脚写一个 `PortPinMode` 参数，取值是 `PORT_PIN_MODE_GPIO`、`ALT1`、`ALT2`、`ALT3`。这个值在厂商 Port 定义里不成立。

用解析器读 `Port_THA6_AS440/config/Port.xdm`，相关参数是：

| 参数 | 含义 | 取值 |
|---|---|---|
| `PortPinMode` | 运行时 `Port_SetPinMode()` 允许切换到的模式 | 只有 `PORT_PIN_MODE_ALL`，不可编辑，默认就是它 |
| `PortPinInitialMode` | `Port_Init()` 时引脚的功能（`GPIO`、`CAN10_TXD` 等） | 由 `Port.OutputModesXDM<hex>` 按引脚给出，默认 `GPIO` |
| `PortPinModeChangeable` | 是否允许运行时切换模式 | 布尔，默认 false |

规则作者想要的应该是"引脚设成什么功能"，也就是 `PortPinInitialMode`，却用了通用名字，写到了另一个参数上。`PORT_PIN_MODE_GPIO` 等四个值都不在厂商定义的取值里。

同类问题还有两处：

- 向导 Port 页的"Default Mode"选项没有作用：向导在生成前把所有 `_option_*` 键丢掉了（`hardware_mapping_wizard.py` 的 `if not key.startswith('_option_')`），所以这个下拉框选什么都不影响结果。
- `data/templates/port/port_gpio_input.yaml`、`port_gpio_output.yaml` 两个配置模板也写 `PortPinMode: PORT_PIN_MODE_GPIO`。

现有测试没有任何一条把映射规则写的参数和厂商定义对照，所以这个问题一直没被发现。

## What Changes

- **Port 规则不再写 `PortPinMode`**：厂商默认值 `PORT_PIN_MODE_ALL` 生效。
- **不写 `PortPinInitialMode`**：引脚保留定义的默认值 `GPIO`；每个引脚可选的功能由配置界面按厂商定义给出。理由见 design.md。
- **向导 Port 页去掉"Default Mode"和"Default Direction"两个选项**：两者都被 `_option_*` 过滤丢弃，没有作用。
- **两个 Port 配置模板去掉 `PortPinMode`**。
- **新增对照测试**：把 `port.yaml` 写的每个参数和取值与厂商 Port 定义对照，参数必须存在，定义列出了取值的枚举，值必须在其中。

## Impact

- Affected specs：`chip-port-pins`（新增需求）
- Affected code：
  - `autosar_configurator/data/mapping_rules/port.yaml`
  - `autosar_configurator/data/templates/port/port_gpio_input.yaml`、`port_gpio_output.yaml`
  - 测试 `tests/core/test_chip_port_pins.py`，新增 `tests/core/test_port_rule_definition.py`
  - 文档：有提到默认模式的地方
- 依赖：`add-chip-ports-from-ecu-resources` 也改了 `port.yaml`，本变更要在它之后实施，并以它为基础。
- 兼容性：
  - Port 映射的输出少了每个引脚的 `PortPinMode` 一项；
  - 已经生成并保存的配置不会被自动改动，里面如果已有 `PORT_PIN_MODE_GPIO`，需要自行处理；
  - 两个配置模板的参数少了 `PortPinMode`。
- **不在本变更范围内**：
  - 让引脚默认方向按端口生效（只读端口不能是输出，需要另做）；
  - 配置模板里其他与厂商定义不一致的参数名（例如输入模板的 `PortPinPullUpDown`，厂商定义里是 `PortPinPullMode`）；
  - 在引脚表里区分输出功能与输入功能，并据此在映射里设置 `PortPinInitialMode`。

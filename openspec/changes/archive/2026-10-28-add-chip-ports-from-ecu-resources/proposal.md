## Why

内置芯片 YAML 的 `ports`（设计器"引脚复用矩阵"页）仍是早期手写的示例数据：每颗芯片 2 到 4 个端口（`PORT_A`…），每个端口 16 个引脚，复用功能是虚构的 `ADC0_CH0`、`TIM0_CH0`。同一文件的 `ecu_resources.Port` 里已经有厂商的真实端口数据。硬件映射向导的 Port、Dio 映射读的是 `ports`，所以生成的端口和引脚与真实芯片对不上。

| 芯片 | 示例引脚表 | 厂商 Port 数据 |
|---|---|---|
| THA610X_LFBGA180 | 2 个端口，32 个引脚 | 16 个端口，123 个引脚 |
| THA6206_LFBGA292 | 3 个端口，48 个引脚 | 17 个端口，146 个引脚 |
| THA6412_BGA516 | 4 个端口，64 个引脚 | 23 个端口，286 个引脚 |

只把引脚表换成真实数据还不够，现有代码有两处会让 Port、Dio 映射出错：

1. **端口序号。** `convert_legacy_chip` 取端口名最后一个字母换算序号（A=0 … P=15），其他名字一律为 0。真实端口号是 0 到 41 之间不连续的数字，换名后所有端口序号都变成 0，引脚编号互相冲突。
2. **引脚编号。** `port.yaml` 用"端口序号 × 16 + 循环计数"计算 `PortPinId`，没有用真实引脚号。端口里有空缺引脚时编号错位：THA6412 的 Port10 没有 12 号引脚，13 号引脚按厂商 `Port.PinId_Port10` 应为 173，规则算出 172。

厂商 Port 插件的模板同样按 `PortNumber * 16 + PinNumber` 计算引脚编号，并用它的十六进制作为 `Port.OutputModes<hex>` 的键后缀，所以映射必须使用真实端口号和引脚号。

## What Changes

- **从 ECU 资源推导引脚表**
  - 端口取 `Port.AvailablePortsID`，每个端口的引脚取 `Port.Port<N>_AvailablePins`。
  - 命名沿用厂商写法：端口 `P<两位端口号>`（如 `P10`），引脚 `<端口>_<引脚号>`（如 `P10_13`），与厂商 ADC 通道名里的 `AN17_P40_10`、`P01_5` 一致。
  - 复用功能取 `Port.InputModesXDM<hex>` 与 `Port.OutputModesXDM<hex>`，`<hex>` 是 GPIO 编号（端口号 × 16 + 引脚号）的小写十六进制。
  - 默认方向为输入；`Port.AvailableReadOnlyPorts` 里的端口只列输入功能。
- **端口序号与真实引脚号**：端口名以数字结尾时取该数字（`P10` → 10），以 A–P 结尾的旧名字照旧按字母换算；`gpio_port` 增加真实引脚号列表 `pins`，显示名不再只取名字最后一个字符。
- **映射规则**：Port 规则按 `pins` 迭代，`PortPinId = 端口序号 × 16 + 引脚号`，子容器名使用真实引脚号；Dio 规则按 `端口序号 × 16 + 引脚号` 计算，但 `gpio_pin` 此前没有 `port_index` 属性，所有 Dio 通道号都是无效值（实施时发现），现在每个引脚带上 `port_index`。
- **设计器第 3 页**新增"从 ECU 资源生成引脚表"：已有引脚且内容会改变时先列出差异并确认，默认"否"，与外设页的推导按钮一致。
- **诊断**：引脚表的端口集合与 `Port.AvailablePortsID` 不一致时给出警告，只提示不阻止保存。
- **内置芯片**：三颗芯片的 `ports` 换成推导结果，重新计算校验和；测试保证引脚表与 ECU 资源一致。

## Impact

- Affected specs: `chip-port-pins`（新增能力）
- Affected code:
  - `autosar_configurator/core/hardware/ecu_resource_diagnostics.py`（推导引脚表、一致性警告）
  - `autosar_configurator/core/hardware/generic_resource.py`（端口序号、`pins`、显示名）
  - `autosar_configurator/data/mapping_rules/port.yaml`（按真实引脚号迭代）；`dio.yaml` 不改（`gpio_pin` 补上 `port_index` 后结果正确）
  - `autosar_configurator/ui/dialogs/chip_definition_designer_dialog.py`（第 3 页按钮）
  - 内置芯片 `autosar_configurator/data/chips/*.yaml`
  - 测试 `tests/core/`、`tests/ui/`；文档 `doc/chip_ecu_resources.md`、`doc/芯片定义设计器使用说明.html`
- 兼容性：
  - 以 A–P 结尾、引脚号连续的旧引脚表，`PortPinId` 与 Dio 的映射结果不变；Port 子容器名加下划线分隔（`PortPin_PORT_A0` 变为 `PortPin_PORT_A_0`）。Port 映射在提交 `c7f3763` 之前一直无法生成动作，没有既有配置依赖旧名字。
  - 内置芯片的 Port、Dio 映射结果会改变：容器名从 `PortContainer_PORT_A` 变为 `PortContainer_P00` 这类名字，引脚编号变为厂商编号。已固化到项目的芯片副本不受影响，项目会提示"芯片库有不同版本"。
- **不在本变更范围内**：
  - 物理封装球号（厂商 .properties 里没有）。
  - 引脚电气属性（驱动强度、上下拉等）以及 LVDS 对、模拟输入等特殊功能。
  - 由引脚表反向生成 `Port.*` 键。

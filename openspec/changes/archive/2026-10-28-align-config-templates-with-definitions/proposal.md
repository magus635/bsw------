## Why

配置模板（`data/templates/*.yaml` 和 `template_manager.py` 里的内置模板）写了不少厂商定义里不存在的参数名或取值。`apply_template` 对每个参数只做 `try/except` 加一行 `print`，失败的参数被静默跳过，用户拿到的是缺了关键项的配置。

用 `EcucDefParser` 逐个对照厂商定义，扫出的不一致：

| 模板 | 问题 |
|---|---|
| Port GPIO Input | `PortPinPullUpDown` 不存在，厂商是 `PortPinPullMode`，取值 `PORT_INPUTMODE_NONE/PULLUP/PULLDOWN` |
| Can 两个模板（YAML 与内置） | `CanControllerRx/TxProcessing`、`CanControllerBusoffProcessing` 应为 `CanRx/TxProcessing`、`CanBusoffProcessing`；`CanControllerDefaultBaudrate`、`CanControllerFdBaudRate`、`CanControllerFdBaudrateConfig` 不在 `CanController` 容器里（波特率在子容器 `CanControllerBaudrateConfig`） |
| Dio 两个模板 | `DioChannelDirection`、`DioChannelInitValue` 不存在（方向由 Port 决定） |
| Spi Master Basic | `SpiTransferStart` 的取值是 `MSB`/`LSB`，不带 `SPI_TRANSFER_START_` 前缀 |
| ADC Single Channel（内置） | 容器 `AdcGroupDefinition` 不存在；`AdcChannelId` 不是 AdcGroup 的参数 |

现有测试没有把模板和厂商定义对照。这是 `fix-port-pin-mode-mapping` 里"待对齐"的那一项。

## What Changes

- 能对应上的改成厂商的名字和取值：`PortPinPullMode`、`CanRx/Tx/BusoffProcessing`、`CanFDSupport`、Spi 的 `MSB/LSB`；ADC 内置模板改用 `AdcConfigSet/AdcHwUnit/AdcGroup` 和 `AdcGroupId`。
- 对应不上的去掉：Can 的波特率参数（模板只作用于单个容器，放不下子容器里的参数）、Dio 的方向和初始值。描述里如实写明波特率在哪里设置。
- Can 的处理方式取值加上厂商定义里有的 `MIXED`。
- 新增对照测试：每个模板的容器路径、参数名、枚举取值都必须在厂商定义里。

## Impact

- Affected specs：`config-templates`（新增）
- Affected code：`data/templates/{can,dio,port,spi}/*.yaml`、`core/template_manager.py`；新增 `tests/core/test_template_definition.py`
- 兼容性：Can 两个模板的波特率输入、Dio 两个模板的方向和初始值输入不再出现（它们本来也设置不上）；模板名不变。Dio 输入和输出两个模板现在只剩通道号，内容相同。
- **不在本变更范围内**：让模板能设置子容器里的参数（波特率）；合并重复的 Dio 模板。

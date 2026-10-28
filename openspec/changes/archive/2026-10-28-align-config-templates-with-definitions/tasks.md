## 1. 模板

- [x] 1.1 Port 输入模板改用 `PortPinPullMode` 及其取值
- [x] 1.2 Can 两个模板（YAML 与内置）：改名 `CanRx/Tx/BusoffProcessing`，`CanFDSupport`，去掉波特率参数，加 `MIXED`，描述里写明波特率的位置
- [x] 1.3 Dio 两个模板去掉方向和初始值
- [x] 1.4 Spi 的 `SpiTransferStart` 取值改为 `MSB`/`LSB`
- [x] 1.5 ADC 内置模板改用 `AdcGroup` 容器和 `AdcGroupId`

## 2. 测试与验证

- [x] 2.1 新增 `tests/core/test_template_definition.py`：对所有模板对照厂商定义
- [x] 2.2 确认测试在修改前失败（扫描时 5 个 YAML 模板和 2 个内置模板有问题）
- [x] 2.3 全量测试通过

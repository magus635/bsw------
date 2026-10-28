## 1. 推导与数据模型

- [x] 1.1 `ports_from_ecu()`：按 `Port.AvailablePortsID`、`Port.Port<N>_AvailablePins` 生成 `P<NN>` 端口与 `P<NN>_<pin>` 引脚；功能名取 `InputModesXDM<hex>` / `OutputModesXDM<hex>`；只读端口只取输入功能；没有 Port 数据时返回空
- [x] 1.2 对照 `Port.xdm` 确认输出功能名与模式号的对应关系，决定是否写 `alt_modes`（结论写回 design.md）
  - 结论：模式取值是名字，不写 `alt_modes`
- [x] 1.3 `convert_legacy_chip`：端口序号按"数字结尾取数字、A–P 结尾按字母"解析，其余为 0 并警告；`gpio_port` 增加 `pins`；显示名使用完整端口名
- [x] 1.4 单元测试：空缺引脚、只读端口、无 Port 数据、十六进制键后缀、旧字母端口名

## 2. 映射规则

- [x] 2.1 `port.yaml` 按 `resource.properties.pins` 迭代，`PortPinId = port_index * 16 + pin`，子容器名用真实引脚号
- [x] 2.2 核对 Port 定义是否需要写 `PortNumber`，需要则加入规则
  - 结论：不可编辑、按容器位置推出，不写；容器顺序与 `AvailablePortsID` 一致并有测试
- [x] 2.3 测试：THA6412 `P10_13` 的 `PortPinId` 与 Dio 通道号都是 173；`P00` 与 `P10` 的 0 号引脚分别为 0 和 160；旧 `PORT_A`/`PORT_B` 芯片的 `PortPinId` 与修改前相同，Port 子容器名为 `PortPin_PORT_A_0` 形式
  - 发现 Dio 通道号原本一直是 `False`（`gpio_pin` 没有 `port_index`），已修正，`PORT_B` 1 号引脚现为 17

## 3. 设计器与诊断

- [x] 3.1 第 3 页"从 ECU 资源生成引脚表"按钮：内容会改变时列出差异并确认，默认"否"；选"否"不改动；引脚表为空时不询问
- [x] 3.2 一致性警告：引脚表端口号集合与 `Port.AvailablePortsID` 不一致时提示缺少与多出的端口
- [x] 3.3 UI 测试：确认、拒绝、空表三种情况；警告文本

## 4. 内置芯片与文档

- [x] 4.1 用推导结果重写三颗内置芯片的 `ports`（先确认原样重存逐字相同），重新计算校验和
- [x] 4.2 测试：内置芯片的 `ports` 等于 `ports_from_ecu(ecu_resources)`；校验和有效
- [x] 4.3 实测 THA6412 的 Port、Dio 向导页建表与生成映射耗时
  - 结果：映射约 5 ms / 4 ms，建表约 9 ms / 38 ms
- [x] 4.4 更新 `doc/chip_ecu_resources.md` 与 `doc/芯片定义设计器使用说明.html`
- [x] 4.5 全量测试通过（`QT_QPA_PLATFORM=offscreen python3 -m pytest tests -q`）：1184 passed，5 skipped

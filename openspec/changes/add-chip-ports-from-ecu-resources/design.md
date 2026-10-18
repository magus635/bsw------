## Context

`ecu_resources.Port` 的相关键（以 THA6412 为例）：

| 键 | 含义 | 示例 |
|---|---|---|
| `Port.AvailablePortsID` | 可用端口号 | `_0_ _1_ _2_ _10_ … _41_` |
| `Port.Port<N>_AvailablePins` | 端口 N 的可用引脚号 | Port10：`_0_ … _11_ _13_ _14_ _15_` |
| `Port.PinId_Port<N>` | 引脚的 GPIO 编号 | Port10：`_160_ … _171_ _173_ …` |
| `Port.InputModesXDM<hex>` | 该 GPIO 的输入功能名 | `InputModesXDMa0`：`GPIO CAN00_RXDH …` |
| `Port.OutputModesXDM<hex>` | 该 GPIO 的输出功能名 | `OutputModesXDM0`：`GPIO GTM_TOUT9 …` |
| `Port.OutputModes<hex>` | 该 GPIO 支持的输出模式号 | `OutputModes0`：`_O0_ _O1_ _O2_ _O3_ _O5_ _O6_ _O7_` |
| `Port.AvailableReadOnlyPorts` | 只读（仅输入）端口号 | |

GPIO 编号 = 端口号 × 16 + 引脚号；`<hex>` 是它的小写十六进制且不补零。厂商 `Port.m` 也按 `PortNumber * 16 + PinNumber` 计算 `PortPinId`，并以其十六进制查 `Port.OutputModes`。

值以 `_n_` 记号写成空格分隔的字符串，导入后在 `ecu_resources` 里仍是字符串，推导时按 `_(\d+)_` 解析。

## Goals / Non-Goals

- Goals：内置与新建芯片的引脚表来自厂商数据；Port、Dio 映射得到与厂商模板一致的端口号和引脚编号；设计器可一键生成引脚表；引脚表与 Port 数据不一致时可见。
- Non-Goals：封装球号、引脚电气属性、LVDS 与模拟输入等特殊功能、由引脚表反向生成 `Port.*`。

## Decisions

- **推导放在 `ecu_resource_diagnostics`，与 `peripherals_from_ecu` 并列**（`ports_from_ecu(ecu_resources) -> Dict[str, List[PortPinDef]]`）。引脚表是 `ChipDefinition.ports`，不是 `resources`，所以单独一个函数，不混进外设推导。
- **命名 `P<NN>` / `P<NN>_<pin>`**：厂商 ADC 通道名使用 `P40_10`、`P01_5` 这种写法，沿用它最容易与厂商文档对照。备选 `Port10`、`PORT_10` 与厂商文档不一致，不采用。
- **端口序号从名字解析**：以数字结尾取数字；以 A–P 结尾按字母换算（保持旧芯片与测试的结果）；都不是时为 0 并写警告。备选"在 YAML 的 `ports` 里加端口级字段"需要改 YAML 格式与导出，收益不大，不采用。
- **`gpio_port.pins` 与 Port 规则**：`convert_legacy_chip` 给 `gpio_port` 加 `pins`（真实引脚号，升序）；`port.yaml` 改为 `iterate: "resource.properties.pins"`，`iterate_var: "pin"`，子容器名 `PortPin_{resource.resource_id}_{pin}`，`PortPinId` 为 `resource.properties.port_index * 16 + pin`。`pin_count` 保留。子容器名加下划线，是为了让 `P10` 的 13 号引脚读作 `PortPin_P10_13` 而不是 `PortPin_P1013`。
- **复用功能**：`alternate_functions` = 输入功能名与输出功能名按出现顺序合并去重（`GPIO` 只出现一次）。只读端口只取输入功能名。
- **模式号表 `alt_modes` 暂不写入**：`OutputModesXDM0` 有 8 个名字（含 `GPIO`），`OutputModes0` 只有 7 个模式号，名字与模式号的对应规则需要对照 `Port.xdm` 的模式枚举确认（见 Open Questions）。确认之前只写功能名，避免写入错误的模式号。
- **设计器按钮的确认方式**与外设页的"从 ECU 资源推导外设"一致：已有引脚且推导结果不同才询问，默认"否"，选"否"不改动。
- **一致性警告**：比较引脚表端口号集合与 `Port.AvailablePortsID`；端口号按上面的解析规则取得，以字母命名的示例端口会因此被报出，这正是希望看到的提示。

## Risks / Trade-offs

- 内置芯片的 Port、Dio 映射结果改变 → 只影响新映射；已固化到项目的芯片副本不变，项目诊断会提示芯片库有新版本。
- THA6412 的引脚表变为 286 个引脚，Port 页与 Dio 页的映射动作数量随之增加 → 实测建表和生成映射的耗时，若超过 1 秒再考虑分页或默认不勾选。
- 名字解析规则若遇到既非数字也非 A–P 结尾的端口名会退回 0 → 写警告，并在一致性检查里报出。

## Migration Plan

1. 实现推导与映射修正，旧引脚表的映射结果用现有测试锁定不变。
2. 用设计器同样的代码路径重写三颗内置芯片的 `ports`，原样重存校验通过后再写入。
3. 更新文档。回退时恢复三份 YAML 与 `port.yaml` 即可。

## Open Questions

- `OutputModesXDM<hex>` 名字与 `OutputModes<hex>` 模式号如何一一对应（`GPIO` 是否对应 `O0`）？需在实现时读 `Port.xdm` 的 `PortPinMode` 枚举确认；确认后再决定是否写 `alt_modes`。
- 厂商 Port 定义中端口容器是否有 `PortNumber` 参数需要由映射规则写入（`Port.m` 读取 `./PortNumber`）？实现时核对 Port 定义后决定是否在 `port.yaml` 增加该参数。

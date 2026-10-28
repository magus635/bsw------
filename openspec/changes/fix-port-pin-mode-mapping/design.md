## Context

厂商 Port 定义（`Port_THA6_AS440/config/Port.xdm`）里与引脚功能有关的参数：

| 参数 | 取值范围的来源 |
|---|---|
| `PortPinInitialMode` | `ecu:get('Port.OutputModesXDM<hex>')`，没有该键时退回 `Port.OutputModesXDMxx`；默认 `GPIO` |
| `RxMuxFunSelect` | `ecu:get('Port.InputModesXDM<hex>')`，没有该键时退回 `Port.InputModesXDMxx`；默认 `GPIO` |
| `PortPinMode` | 固定为 `PORT_PIN_MODE_ALL`，不可编辑 |

`<hex>` 是端口号×16+引脚号的小写十六进制。

厂商自己保存的配置可以作为参照：`doc/THA6XXX_MC_AS440/DemoWorkspace/CodeProject/DemoMcal/Config/THA6412_BGA516/output/Port.epc` 有 286 个引脚（与引脚表推导出的 286 个一致），其中 `PortPinMode` 全部是 `PORT_PIN_MODE_ALL`；`PortPinInitialMode` 有 237 个是 `GPIO`，其余是 `MSC0_SOP` 这类具体功能名。也就是说，厂商的配置从不使用 `PORT_PIN_MODE_GPIO`，而 `GPIO` 是 `PortPinInitialMode` 的值。

规则文件 `port.yaml` 现在写的参数：`PortNumberOfPortPins`、`PortPinId`、`PortPinDirection`、`PortPinLevelValue`、`PortPinMode`。用 `EcucDefParser` 逐个对照厂商定义：前四个都存在，取值合法；只有 `PortPinMode` 的四个取值全部不在定义的取值里。

## Goals / Non-Goals

- Goals：映射不再写厂商定义不接受的值；以后规则写了不合法的参数或取值时，测试能发现。
- Non-Goals：见 proposal 的"不在本变更范围内"。

## Decisions

- **不写 `PortPinInitialMode`，而不是改成按引脚设置。** 曾考虑过"把 `PortPinMode` 改成 `PortPinInitialMode`，选项取引脚的功能名"，不采用：
  1. 取值范围来自 `OutputModesXDM`（输出功能），而引脚表的 `alternate_functions` 是输入名和输出名合并后的列表。实测 THA6412 的 261 个有输出表的引脚，每一个都带有不在输出表里的输入名（例如 `GTM_TIM2_IN0_1`），按它给选项会混进不合法的值。输入名对应的是另一个参数 `RxMuxFunSelect`。
  2. 只读端口（`P40`、`P41`）没有自己的输出表，定义对它们退回 `OutputModesXDMxx`，引脚表里没有对应的数据。
  3. 厂商默认值 `GPIO` 对每个引脚都成立，配置界面又按定义给出每个引脚的合法范围，向导没有必要替用户选。
  
  要在映射里设置初始功能，需要引脚表分别保存输出功能和输入功能，这会改动芯片 YAML 的格式、校验和、设计器的引脚表和引脚表导入，代价大于收益，留作以后的变更。
- **也不写 `PortPinMode = PORT_PIN_MODE_ALL`。** 它是定义的默认值，而且不可编辑，写入没有任何作用。
- **去掉"Default Mode"，保留"Default Direction"。** "Default Mode"是为 `PortPinMode` 准备的，参数没了它就没有意义。"Default Direction"同样没有作用（`_option_*` 键被丢弃），但如果让它生效，会给只读端口写 `PORT_PIN_OUT`，而定义明确把这种组合判为无效（`Port.xdm` 中 `PortPinDirection` 的 INVALID 条件）。要让它生效，映射必须按端口区分只读端口，这是单独的功能，不放进这次修正。
- **对照测试用 `EcucDefParser.parse_module_def_file` 读 `Port.xdm`**，与 `test_chip_single_source.py` 读 `Resource.xdm` 的做法一致，不新增解析代码。
  - 对规则里的每个参数检查它在定义中存在，并且在定义列出了取值时，值在其中；
  - 容器名按规则里 `path_template` 的最后一段区分（`PortContainer`、`PortPin`）；
  - `PortPinInitialMode` 的取值是运行时按 ECU 数据决定的（解析出的取值列表为空），无法静态对照，所以规则不写它，测试也不检查它；
  - 测试不依赖项目里是否有 `test_import_project`：沿用现有测试直接引用该目录的做法。
- **配置模板只去掉 `PortPinMode`。** 两个模板里还有别的与厂商定义不一致的名字（`PortPinPullUpDown`），这属于模板整体与厂商定义的对齐，范围更大，本变更只处理与 `PortPinMode` 相同的问题。

## Risks / Trade-offs

- 已保存的配置里如果有 `PORT_PIN_MODE_GPIO`，本变更不会改动它。没有验证过配置界面对这种值的处理（定义里这个参数不可编辑）。
- 取消"Default Mode"后，向导 Port 页少一个下拉框。它本来就不起作用，所以用户看到的结果没有变化。
- 本变更之后，Port 映射仍然不替用户选引脚功能：这是有意的，选择在配置界面里完成。

## Migration Plan

没有数据迁移。回退时恢复 `port.yaml` 和两个模板即可。

## Open Questions

- "Default Direction"是删掉，还是按端口区分只读端口后让它生效？
- 两个配置模板里还有哪些参数名与厂商定义不一致，是否值得单独做一次对齐？

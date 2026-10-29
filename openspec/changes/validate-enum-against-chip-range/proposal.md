## Why

枚举参数的可选范围有两种来源：定义里写死的选项，和定义里 `RANGE` 写成 `ecu:list('X.Y')`、由所选芯片的 ECU 资源给出的列表。

校验（`EnumerationValidationRule`）只看 `param_def.literals`：

- 打开工程时，定义在没有芯片数据的情况下解析，`ecu:list` 算不出来，`literals` 为空，校验对这些参数**什么都不查**。
- 在界面里手动添加模块时，`literals` 是添加那一刻的芯片列表；之后换了芯片，校验仍按旧芯片的列表查。

配置面板显示时会按当前芯片重新取范围，并把不在范围的值标成"（不在可选范围）"，但只有点开那个参数才看得到。生成前不跑校验，所以一个当前芯片上不存在的硬件单元（比如 THA610X 上的 `SARADC8`）能一路生成进代码。

实测（厂商示例工程 `doc/THA6XXX_MC_AS440/DemoWorkspace`，定义来自 `test_import_project/Def/plugins`）：

- 厂商 xdm 里范围为 `ecu:list` 的枚举参数：THA6412 / THA6206 的模块里 46 个是单纯的 `ecu:list('X.Y')`，28 个是更复杂的表达式。
- 三套示例配置对各自的芯片：分别检查了 2554、1565、995 个值，**不在范围的为 0**。
- 把 THA6412 的配置放到 THA610X 的芯片数据上查：93 个值不在范围，例如 `Adc.HwUnitId` 的 `SARADC8`、`Dma.HwUnitList` 的 `DMA1`、`Resource.AvailableCores` 的 `CORE2`。现在的校验一条都不报。

## What Changes

- 枚举校验在有工程上下文时，对范围是单纯 `ecu:list('X.Y')` 的参数，按工程**当前**的 ECU 资源（`project.ecu_resources`，即芯片 YAML 合并 `.properties` 的结果）取范围来查，取代解析时留下的 `literals`。
- 键的匹配和生成时的 `ecu:get` 一致：先精确匹配，再忽略大小写。值是逗号分隔的字符串时按逗号拆开。
- 不在范围的值报 **错误**，和现在"不在定义的固定选项里"同级。消息里写明范围来自哪个 ECU 资源键和哪颗芯片，修复建议列出可选值。
- 下列情况保持现状（按 `literals` 查，没有就不查）：
  - 没有工程上下文（单模块模式）
  - 范围不是单纯的 `ecu:list`
  - 工程的 ECU 资源里没有这个键（缺键已由 ECU 资源诊断报告，这里不重复）
  - 解析出的列表为空

## Impact

- Affected specs：`config-validation`（新增）
- Affected code：`autosar_configurator/core/rules/base_rules.py` 的 `EnumerationValidationRule`（`validate` 接收 `project_context`，`_validate_enum` 选择范围来源）。
- 兼容性：只多报错误，不改配置、不改生成、不阻止生成；配置面板不变。厂商示例配置上不产生新的报告。
- **不在本变更范围内**（后续另提）：
  - 复杂的范围表达式（`text:concat`、`node:when` 等，示例工程里 28 个）；
  - 芯片数据覆盖 `.properties` 或配置 ARXML 时的提示；
  - 打开工程或换芯片后按芯片重算定义的默认值和最大个数；
  - 生成前自动校验。

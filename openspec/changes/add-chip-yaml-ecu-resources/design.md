## Context

- `ecu:get/ecu:list` 读取 `BuiltinFunctions.ecu_resources`（扁平字典，键如 `Resource.NumOfCores`，大小写不敏感查找）。来源目前只有 `.properties` 解析结果。
- 现有读取点：`WorkspaceProject.load_ecu_resources()`（UI 浏览用，含模块定义路径）与 `CodeGenerator._load_ecu_resources()`（生成用，扫 `Def/`、`Define/` 与模板目录）。生成器已支持构造参数 `ecu_resources`，但四个调用点都没有传。
- 厂商文件示例：`Os_Resource_THA6412.properties`（`OsResource.*` 5 项、`Os.*` 5 项，其中 `Os.IsrTriggerMethodList` 992 项）；`CotexR52_THA6412_BGA516.properties`（`Resource.*`、`Adc.*`、`Can.*` 等，含 `Adc.SyncGroup.Master.SARADC0: 0, 1, 1, 1` 这类未结构化键，以及原文拼写 `Resource.Clsuter.C0.Cores`）。

## Goals / Non-Goals

- Goals：YAML 成为权威来源；新建项目也能得到与导入项目等价的 `ecu_resources`；properties 与 YAML 之间无损往返；缺键能被发现。
- Non-Goals：不读 / 不写 `plugin.xml`；不引入项目级覆盖；不对键做语义建模（除一致性检查用到的少数已知键）；不改变模板语言与 `ecu:*` 函数的行为。

## Decisions

### D1 YAML 结构：按模块分组、完整键保持不变

```yaml
name: THA6412_BGA516
# ...
resource_version: 1.0.0
ecu_resources:
  OsResource:
    NumOfCores: 4
    AvailableCores: [CORE0, CORE1, CORE2, CORE3]
    MasterCore: OS_CORE_ID_0
    MultiCoreModules: [ADC, PWM, GPT, CAN, SPI, ETH, LIN, ICU, OCU, UART, MSC, DMA, IOM, SENT, DSADC, I2C]
    SupportProcessor: THA6412
  Os:
    GicIntTriggerMethod: [EDGE, LEVEL]
    IsrTriggerMethodList: [1, 1, 1, 1]   # 实际 992 项
  Resource:
    Clsuter.C0.Cores: [CORE0, CORE1]      # 键名保持原文，不修正拼写
```

- 展开后得到扁平键 `<Module>.<name>`，与 `TresosPropertiesFile.properties` 的键完全相同，所以 `ecu:*` 消费端不需要改动。
- 模块名取键的第一个 `.` 之前，与 `TresosPropertiesParser` 已有的 `resources` 分组一致，导入导出用的是同一条规则。
- 单值 → 标量，多值 → 列表（与现有 `_parse_value` 一致）。不为未结构化的键设计专门字段，统一放这里，保证无损。
- 备选（不采用）：把核数、主核做成 `ChipDefinition` 的专门字段。优点是类型明确，缺点是每遇到新键都要改模型，且与"原样保存"目标冲突。

### D2 来源优先级

`插件 properties（低） < 芯片 YAML（高）`，同键冲突时 YAML 胜出，并记录一条 INFO 级日志（键、两个值）。理由：YAML 是权威。properties 的作用是 EB 导入项目里已有的内容，以及 YAML 尚未覆盖某模块时的后备，使迁移可以渐进。

### D3 统一入口 EcuResourceResolver

输入：项目（路径、模块定义路径、`selected_chip`）与 `ChipDatabase`。输出：扁平字典，赋给 `project.ecu_resources`。

- properties 部分直接复用现有 `WorkspaceProject.load_ecu_resources()` 的扫描与过滤逻辑（搬入 Resolver，行为不变）。
- 触发时机：新建项目、打开项目、导入 EB 项目、添加模块、更换芯片。
- 更换芯片时必须整体重算，不能在旧字典上叠加，否则旧芯片的键会残留。

### D4 生成器不再自己扫描

四个调用点传 `ecu_resources=project.ecu_resources`。`CodeGenerator._load_ecu_resources()` 保留，仅用于没有 `project.ecu_resources` 的场景（脚本、测试）。保证两处不再各自实现一套匹配规则。

### D1a 长列表的区间写法

列表值除了普通列表，还可以写成"下标区间 → 值"的映射：

```yaml
Os:
  IsrTriggerMethodList:
    0-15: 1          # 下标 0..15 共 16 项，值为 1
    16-18: 2
    19-21: 4
    22: 2            # 单个下标
```

- 键为 `<起>-<止>`（含两端）或单个下标；所有键的并集必须恰好覆盖 `0..N-1`，不允许缺口、重叠、超出或乱序键造成的歧义，否则加载失败并指出键。
- 加载后立即展开为完整列表，之后的一切（`ecu:*`、导出 properties、诊断）只看展开后的列表，区间写法只是书写形式。
- YAML 导出时：列表至少 16 项且区间写法的条目数少于列表项数时，输出区间写法，否则输出普通列表。这条规则只依赖数据本身，所以输出是确定的。
- 区间值只接受标量；值类型与普通列表相同。

### D5 导出：只写数据里有的

导出主要用于往返校验和迁移时对照，不是给 EB 用户的发布物（客户不在 EB 中使用）。`to_properties_string` 新增分支：当 `chip.ecu_resources` 非空时，按模块各输出一个文件，键与值逐项取自 `ecu_resources`；不补充任何默认值或硬编码常量。没有 `ecu_resources` 的芯片继续走旧逻辑，旧输出不变，已有测试不改。

- 写出顺序：模块按 YAML 中出现的顺序，键按 YAML 中的顺序，保证确定性（与 CLAUDE.md 的"确定性排序"一致）。
- 导出文件头的版本、文件名取自 `resource_version` 与芯片名，不再写死 `Autosar Version : 4.4.0`。

### D6 诊断

1. **键需求扫描**：复用 `extract_xdm_resources()` 扫描已加载模块的 xdm；模板中的引用用同一正则扫描 `templates/{Module}/`。得到"被引用的键集合 R"。
2. **比对**：`R − keys` = 缺失键（会静默生成空值，提示用户）；`keys − R` = 未被引用键（仅信息，不当作错误，因为同一文件里还有给其他模块用的键）。
3. **一致性检查**：只针对明确的规则，以表的形式声明，新增规则不改流程：
   - `OsResource.NumOfCores` 等于 `OsResource.AvailableCores` 的元素个数；
   - `OsResource.MasterCore`（以及 `Resource.MasterCore` 的每个元素）必须是 `CORE<n>` 写法，并且属于 `AvailableCores`；不是该写法的值（例如 `OS_CORE_ID_0`）报告"不是 CORE<n> 形式"，**不做静默转换**；
   - `Os.IocPrimitiveDataTypeNum` 等于 `Os.IocPrimitiveDataType` 的元素个数。
4. 诊断只提示，不阻断生成。

### D7 为什么不把 992 项触发方式拆成结构

它只是被模板按下标读取的序列，拆开没有收益；按列表保存，过长时用 D1a 的区间写法书写。

## Risks / Trade-offs

- **双份数据漂移。** 导出的 properties 若被人手改，下一次导入会被 YAML 覆盖，反过来也一样。缓解：约定 properties 为生成物，文件头写明"由 YAML 生成，请勿手改"。
- **主核写法与 Os 模板。** 厂商的 `Os_Resource_THA6412.properties` 里 `OsResource.MasterCore` 是 `OS_CORE_ID_0`，而本设计要求 `CORE<n>` 写法。导入时值原样保存，会触发"不是 CORE<n> 形式"的警告；如果 Os 模板（不在本仓库）按 `OS_CORE_ID_<n>` 取值，把 YAML 里的值改成 `CORE0` 会改变生成结果。因此该值是否改写，必须在带 Os 插件的真实项目里对照生成结果后再定（见 tasks 8.4），本变更不自动转换。
- **键名拼写不可修正。** 模板里写死了原文拼写（`Clsuter`），保持原样。
- **指纹。** 来源优先级变化可能改变某个已有 EB 项目的 `ecu:get()` 结果。缓解：对导入路径做黄金对比，`verify_fingerprints.py` 必须无变化。
- **诊断误报。** 模板里用拼接构造的键（如 `'Adc.SyncGroup.' + $unit`）无法静态扫描，会被误判为未引用。缓解：扫描器只负责"缺失"提示，把"未引用"降到 INFO，并在日志说明静态扫描的局限。

## Migration Plan

1. 先加 `ecu_resources` 字段与 YAML / properties 互转，不改任何调用点，保证完全向后兼容。
2. 引入 Resolver，先只在新建项目路径接入；导入与打开路径委托后需通过黄金对比。
3. 生成器改用项目字典。
4. 诊断功能最后加入。
5. 回滚：去掉调用点传参即可退回旧的扫描路径。

## Resolved Decisions

1. 首批导入与往返验证只覆盖 `Os_Resource_*.properties` 与 `CotexR52_*.properties` 两类；其他模块的资源文件以后再扩展。
2. 主核统一用 `CORE<n>` 写法；不是该写法的值只报警，不自动转换（见 D6、Risks）。
3. 长列表允许区间写法（见 D1a）。
4. 客户不会在 EB Tresos 里使用导出的 properties，`plugin.xml` 的 `ecuresource` 不在范围内，也不需要后续提案。

## Open Questions

1. `OsResource.MasterCore` 在 Os 模板中实际按哪种写法读取？需要在带 Os 插件的项目上确认（tasks 8.4）。
2. 区间写法的导出阈值（≥ 16 项且条目数更少）是否合适，可在实现时用真实数据调整。

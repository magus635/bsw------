# 芯片 ECU 资源（`ecu_resources`）

模板和 xdm 里的 `ecu:get()` / `ecu:list()` 读取"按芯片区分的资源常量"（核数、核名、主核、ISR 触发方式……）。
这些常量现在由**芯片 YAML**维护；EB Tresos 的 `.properties` 文件只作为迁移时的导入来源，以及往返校验用的导出产物。

## YAML 格式

在 `autosar_configurator/data/chips/<芯片名>.yaml` 里增加可选的 `ecu_resources` 与 `resource_version`：

```yaml
name: THA6412_BGA516
resource_version: 1.0.0
ecu_resources:
  OsResource:
    NumOfCores: 4
    AvailableCores: [CORE0, CORE1, CORE2, CORE3]
    MasterCore: CORE0
    MultiCoreModules: [ADC, PWM, GPT, CAN, SPI, ETH, LIN, ICU, OCU, UART, MSC, DMA, IOM, SENT, DSADC, I2C]
    SupportProcessor: THA6412
  Os:
    GicIntTriggerMethod: [EDGE, LEVEL]
    IsrTriggerMethodList:      # 下标区间写法，见下
      0-15: 1
      16-18: 2
      19-21: 4
  Resource:
    Clsuter.C0.Cores: [CORE0, CORE1]   # 键名保持模板里的原文拼写
```

- 模块名（`OsResource`、`Os`、`Resource`……）是完整键 `<模块>.<名字>` 中第一个 `.` 之前的部分，**不能含 `.`**；名字里可以有 `.`（如 `SyncGroup.Master.SARADC0`）。
- 值是标量（数字、布尔、字符串）或标量列表。不能是嵌套列表，也不能是普通映射。
- 没有 `ecu_resources` 的 YAML 完全按原样加载，不需要修改。

### 下标区间写法

长列表可以写成"下标区间 → 值"的映射，加载时展开成完整列表：

| 写法 | 含义 |
|---|---|
| `0-15: 1` | 下标 0..15（含两端）都是 1 |
| `22: 2` | 单个下标 |

所有区间合起来必须恰好覆盖 `0..N-1`：缺口（`missing index 4`）、重叠、起止颠倒、值不是标量，都会让加载失败，错误信息里带文件名和键名。
导出 YAML 时，列表至少 16 项且区间条目数少于元素数，才会用区间写法，否则写普通列表。

## 与 `.properties` 的关系

- **导入**：芯片设计器的"导入 .properties 到 ECU 资源…"把文件里的**全部键**并入芯片的 `ecu_resources`（按第一个 `.` 分模块，不做外设建模）；多个文件后者覆盖前者并写日志；没有 `.` 的键无法表示，会被跳过并给出警告。
  代码接口：`ChipDatabase.import_ecu_resources_from_properties(chip, paths)`。
- **导出**：芯片有 `ecu_resources` 时，每个模块写一个 `<模块>_<芯片名>.properties`，内容只来自 `ecu_resources`，不补任何默认值；模块与键的顺序与 YAML 一致，重复导出结果逐字节相同。没有 `ecu_resources` 的芯片仍走旧的导出。
  代码接口：`ChipDefinitionExporter.save_module_properties(chip, dir)`。
- 导出的 `.properties` 是**生成物**，文件头已注明"由 YAML 生成，请勿手改"。改数据请改 YAML。
- 往返校验：properties → YAML → properties → 再导入，得到的键值必须完全相同（`tests/core/test_chip_ecu_resources.py`）。

## 项目里何时生效

`WorkspaceProject.ecu_resources` 由 `EcuResourceResolver` 统一构建（来源优先级：插件 `.properties` < 所选芯片的 YAML，同键冲突 YAML 胜出并写 INFO 日志），在以下时机整体重算：

1. 新建项目（向导里选了芯片）
2. 打开项目
3. 导入 EB 项目
4. 添加模块
5. 更换芯片（项目属性、`ResourceSubderivative` 变化）

生成代码前，`GenerationController` 会再算一次并传给 `CodeGenerator(ecu_resources=...)`；没有项目或结果为空时，生成器才自己扫描 `.properties`。

## 缺键与一致性诊断

`WorkspaceProject.diagnose_ecu_resources()`（新建、导入、添加模块、更换芯片后自动运行，详情写日志，状态栏给出摘要）：

- **缺失键**（警告）：已加载模块的 xdm、`generate_PB/`、`templates/<模块>/` 里以字面量引用的 `ecu:get('…')` / `ecu:list('…')`，在 `ecu_resources` 里没有值。**不会阻断生成**，但这些位置会静默得到空值。
- **未引用键**（信息）：有值但没有任何地方引用。只扫描字面量，字符串拼接构造的键（如 `'Adc.SyncGroup.' & $unit`）不会被发现，所以这里的"未引用"仅供参考。
- **一致性规则**（警告，表在 `ecu_resource_diagnostics.CONSISTENCY_RULES`）：
  - `OsResource.NumOfCores` / `Resource.NumOfCores` 等于对应 `AvailableCores` 的元素个数
  - `OsResource.MasterCore` / `Resource.MasterCore` 的每个值是 `CORE<n>` 写法，且属于 `AvailableCores`；其他写法（如 `OS_CORE_ID_0`）只报警，**不自动转换**
  - `Os.IocPrimitiveDataTypeNum` 等于 `Os.IocPrimitiveDataType` 的元素个数

## 待确认

`OsResource.MasterCore` 在 Os 模板中实际按 `OS_CORE_ID_<n>` 还是 `CORE<n>` 读取，需要在带 Os 插件的真实项目上对照生成结果确认（OpenSpec 任务 8.4）后，再决定 YAML 里写哪种。

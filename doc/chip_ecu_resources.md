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

## 芯片 YAML 属于项目（`chips/`）

软件包里的 `autosar_configurator/data/chips/` 是**芯片库**，只是复制来源。每个项目在自己的目录里保存所选芯片的一份 YAML：`<项目目录>/chips/<芯片名>.yaml`。Resolver 读取项目里的这份，没有时才退回芯片库（日志里有 INFO）。

- **新建项目**选了芯片：自动写入 `chips/`。
- **更换芯片**：项目已有 `chips/` 时，自动把新芯片从芯片库复制进去。
- **旧项目**（没有 `chips/`）：不会自动写文件，状态栏提示"芯片数据尚未保存到项目"。在"项目属性 → ECU/Chip Selection"里点 **Save Chip to Project**：芯片库有该芯片就复制；没有就由项目 `resource/` 目录下匹配所选芯片的 `.properties` 生成（build 配置等文件不会进来）。
- **Update from Library**：用芯片库当前版本替换项目里的副本，先列出有差异的键并确认。芯片库升级**不会**自动影响已有项目。
- 项目整体搬到别的目录后结果不变，项目文件里不记录绝对路径。
- 芯片下拉框合并列出项目内的芯片、芯片库的芯片和 properties 文件名里的芯片。

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
  - `Resource.MasterCore` 的每个值是 `CORE<n>` 写法；`OsResource.MasterCore` 是 `OS_CORE_ID_<n>` 写法（Os 模板把它原样输出为 C 宏名，写成 `CORE0` 会生成未定义标识符）；都必须属于 `AvailableCores`。其他写法只报警，**不自动转换**
  - `Os.IocPrimitiveDataTypeNum` 等于 `Os.IocPrimitiveDataType` 的元素个数

## 芯片设计器的"ECU 资源"页

设计器第 4 页（"4. ECU 资源"）可以编辑芯片的全部 `ecu_resources`，不限于 CAN/ADC/SPI；预览与导出顺延为第 5 页。

- **模块与键**：左边按模块分组的树。"新增模块 / 新增键 / 重命名 / 删除"。模块名不能含 `.`，值只能是标量或标量列表，不合法时提示并保持原样。任何模块（Gtm、Mcu、Dma……）都能新建，不需要为外设单独写代码。
- **值的编辑**（右边，点"应用"后写入）：
  - 标量：单行输入，类型按输入内容推断（`0x10` → 整数，`1.5` → 浮点，`true/false/yes/no/on/off` → 布尔，其余为字符串），下方显示将保存的类型；勾选"按字符串保存"可保留 `007` 这类文本。
  - 列表：逐项编辑，可增删、上移下移；"转为标量 / 转为列表"互转。
  - 长字符串（超过 80 个字符，或带前导空格）：多行编辑，原样保存，保留前导空格（模板依赖它做空格分隔匹配）。
- **区间视图**：列表页的"区间视图"把长列表显示成"下标区间 / 值"，例如 992 项的触发方式只有几行。改完点"应用"后展开成完整列表；有缺口、重叠会被拒绝并指出缺的下标。切换视图不改变值，保存时是否用区间写法仍由数据决定（至少 16 项且区间更少）。
- **搜索与过滤**：按键名、值内容搜索；过滤"待填写"（值为空）或"有问题"（一致性检查提到的键）。
- **所需键引导**："扫描项目模块所需键"（设计器从项目打开时可用）或"从插件目录扫描所需键…"（选插件根目录），列出被 xdm 或模板以字面量引用、本芯片没有值的键，勾选后加入为"待填写"条目（黄色）。
  - 只扫描字面量，字符串拼接构造的键扫不到；被芯片条件保护的键可能被列出，**列表里的键不一定都需要**。
  - 只在其他芯片里有值的键不会推荐。
- **保存时**：还有"待填写"（值为空）的条目时会提示数量，可以继续保存，也可以回去填写。
- **一致性提示**：编辑页底部和预览页显示一致性检查结果，只提示，不阻止保存。
- **旧推导的标注**：芯片没有 `ecu_resources` 时，`.properties` 预览顶部会写明"兜底推导，非权威数据"；该路径里 `Adc.MaxResolution` 取界面上的 ADC 分辨率。`Port.MaxAvailablePortID`（取了端口个数）、Cluster 等旧推导仍有已知问题，所以请在 ECU 资源页导入或填写后再导出。

## 已知限制

- Os 模板只定义了 `OS_CORE_ID_0/1`，4 核芯片的 `OS_CORE_ID_2/3` 在模板里是未定义的（模板问题，不在本功能内）。
- 设计器重新保存时，多个 CAN/ADC/SPI 各自的个性化设置会被全局设置覆盖，`intc_sources` 只能原样带过。
- 不能从引脚表生成 `Port.*` 的模式列表（`InputModes*`、`OutputModes*` 等）。

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

## 一个 YAML 就够：选择器、一致性与校验和

### 界面约束与生成用同一份数据

打开项目后，界面里由 `ecu:get` / `ecu:list` 算出的限制（最大值、取值范围、实例数）取自项目的 ECU 资源，与代码生成完全相同：芯片 YAML 加项目里的 `.properties`。只有芯片 YAML、没有任何 `.properties` 的项目，界面约束同样完整。芯片可选列表合并芯片库、项目 `chips/` 和 properties 文件名。

### 芯片选择器（`selectors`）

模块定义里有"选择器"参数，模板按它分支，例如 `Resource.ResourceSubderivative`、`Os.OsResourceSubderivative`。新芯片在自己的 YAML 里声明取值即可被选择，**不用改定义文件**：

```yaml
selectors:
  Resource.ResourceSubderivative: THA6412_BGA516
  Os.OsResourceSubderivative: Os_THA6412     # Os 的取值命名与芯片名不同，必须显式写
```

- 解析定义时，选择器的可选值 = 定义里原有的值 + 芯片库（及项目 `chips/`）里所有芯片声明的值；原有值保留，默认值不变。
- 用户配置里的选择器取值与所选芯片声明不符时，诊断给出警告，**不会自动改配置**。
- 设计器"基础信息"页的"芯片选择器"表格编辑这一段；有非法行（不是 `模块.参数`、取值为空、重复）时不能保存。
- 内置芯片已声明两个选择器：`Resource.ResourceSubderivative` 取芯片名；`Os.OsResourceSubderivative` 为 `THA610X_LFBGA180 → Os_THA610X`、`THA6206_LFBGA292 → Os_THA6206`、`THA6412_BGA516 → Os_THA6412`。`Os_THA610X` 不在原 `Os.xdm` 的取值范围里，由芯片声明补进去。
- `Os_SC300` 对应芯片 SC300，它目前不在芯片库中（没有 SC300 的芯片 YAML），所以没有芯片声明它；它仍在 `Os.xdm` 原有的取值里，可以照常选择。

### 以 ECU 资源为准

核数、可用核、主核在设计器表单（`metadata.cores`）和 ECU 资源（`OsResource.*`、`Resource.*`）里各有一份。模板只读 ECU 资源，所以以它为准：

- 两者不一致时，"基础信息"页和预览页给出提示；"用 ECU 资源覆盖表单"把表单改成 ECU 资源的值。
- ECU 资源里没有对应键时不比较。`OsResource.MasterCore` 的 `OS_CORE_ID_<n>` 按编号与 `CORE<n>` 比较。

### 校验和与项目记录

- 保存芯片 YAML 时总会写入 `checksum: sha256:...`，按内容计算（与键的顺序、排版无关）。
- 加载时内容与校验和不符（在设计器之外被手改），会提示"已被修改"，但仍然加载。没有 `checksum` 的旧文件不提示。
- 项目文件记录所用芯片的 `{name, resource_version, checksum}`（不含路径），在固化到项目、从芯片库更新、更换芯片时更新。打开项目后，诊断会提示：项目副本在记录之后被改过；芯片库有不同版本（可用 Update from Library）。
- 校验和只用于发现改动，不防恶意篡改。

## 外设实例（`resources`）

芯片的外设实例写在 `resources` 段，类型不限，每个实例的属性各自独立：

```yaml
resources:
  can_controller:
    - {resource_id: CAN0, display_name: CAN Controller 0, properties: {controller_id: 0, supports_fd: true}}
    - {resource_id: CAN1, properties: {controller_id: 1, supports_fd: false}}
  gpt_channel:
    - {resource_id: GPT0, properties: {channel_id: 0}}
```

- `resource_id` 不能为空，同一类型下不能重复；属性值是标量或标量列表。`display_name` 缺省时取 `resource_id`。
- 旧格式的 `can_resources`、`adc_resources`、`spi_resources`、`intc_sources` 仍可读取，加载时转成 `can_controller`、`adc_unit`、`spi_unit`、`intc_source`；保存时只写 `resources`。两种写法都存在时以 `resources` 为准并警告。内置芯片已迁移为新格式（迁移前后数据逐项相同）。
- 引脚仍在 `ports`（设计器"引脚复用矩阵"页）；硬件映射用的 `gpio_port` / `gpio_pin` 由引脚表推导。`resources` 里若直接写了引脚类型的实例（没有引脚表的芯片），会原样保留并参与映射，引脚表推导出的同名实例优先。

### 引脚表来自 ECU 资源（`ports_from_ecu`）

| 键 | 用途 |
|---|---|
| `Port.AvailablePortsID` | 端口号（按此顺序，即 Port 定义里 `PortContainer` 的顺序；`PortNumber` 由定义按容器位置推出，不由映射写入） |
| `Port.Port<N>_AvailablePins` | 端口 N 的引脚号（可以有空缺） |
| `Port.InputModesXDM<hex>` / `Port.OutputModesXDM<hex>` | 引脚的输入、输出功能名，`<hex>` 为端口号×16+引脚号的小写十六进制 |
| `Port.AvailableReadOnlyPorts` | 只读端口：只列输入功能 |

端口名为 `P` 加两位端口号（`P10`），引脚名为 `<端口>_<引脚号>`（`P10_13`），与厂商 ADC 通道名里的写法一致。功能只写名字、不写模式号：Port 定义的 `PortPinInitialMode` 取值本身就是这些名字。映射时 `PortPinId` 与 Dio 通道号都是端口号×16+引脚号，端口号取端口名末尾的数字（以 A–P 结尾的旧名字按字母换算），与 `Port.PinId_Port<N>` 一致。引脚表的端口集合与 `Port.AvailablePortsID` 不一致时，设计器和项目诊断会给出警告，只提示不拦截。内置三颗芯片的 `ports` 就是这样生成的，测试保证两者一致。

### 与硬件映射规则的关系

`data/mapping_rules/*.yaml` 的每条规则对应一种外设类型，并通过 `resource.properties.<名>` 读取实例属性：

| 类型 | 模块 | 规则读取的属性 |
|---|---|---|
| `can_controller` | Can | `controller_id`、`supports_fd` |
| `adc_unit` | Adc | `unit_id`、`resolution_bits`、`channels`、`channel_count` |
| `spi_unit` | Spi | `unit_id`、`supports_dma`、`max_baudrate` |
| `intc_source` | Intc | `is_configurable`、`vector_number` |
| `eth_controller` | Eth | `controller_id` |
| `gpt_channel` / `icu_channel` / `lin_channel` / `pwm_channel` | Gpt / Icu / Lin / Pwm | `channel_id` |
| `wdg_unit` | Wdg | `unit_id` |
| `clock_source` | Mcu | `frequency`、`type` |
| `gpio_port` / `gpio_pin` | Port / Dio | 由引脚表推导 |

### 设计器"外设"页

- 左边是外设类型（带实例数和对应模块），"新增类型"可选规则里的类型，也可直接输入新类型名；引脚类型不在这里编辑。
- 右边是实例表：`resource_id`、`display_name` 和每个属性一列，规则会读的属性列名带 `*`，缺值时标黄，页底提示"硬件映射向导将拿不到 X"。
- "增加实例 / 复制实例 / 删除实例 / 增加属性 / 删除属性"；"批量添加…"按前缀、起始编号、个数生成（如 `CAN0`…`CAN5`），规则里以 `_id` 结尾的属性自动填编号。
- **"🔄 从 ECU 资源推导外设"**：可根据第 4 页 `ecu_resources` 中的硬件常量（`Can`、`Adc`、`Spi`、`Eth`、`Wdg`、`Mcu`、`Gpt`/`Basetimer`、`Lin`/`Asi`、`Intc` 等）一键生成并更新对应的外设实例，同时保留其他自定义外设类型（如 `intc_source`）。已有实例且内容不同的类型会被整类替换，替换前会列出这些类型并要求确认，选“否”则不做任何改动。实例编号和数量取自 ECU 资源（如 `Can.HwUnitNode`、`Adc.HwUnitId`、`Asi.AvailableHWUnit`、`Basetimer.HwUnitList`）；厂商文件里没有的属性只填协议默认值（CAN 1 Mbit/s、SPI 20 MHz、LIN 20 kbit/s），不编造邮箱数、超时范围等芯片参数。中断源 `intc_source` 按 `Intc.IntSrcClass` → `Intc.<类>.SubClassName` → `Intc.<类>.<子类>.IntName` / `IntID` 逐个列出，`vector_number` 取 `IntID`；`Intc.CoreFixedIntClass` 里的类（每个核私有的 SGI/PPI/软中断）`is_configurable` 为 false，映射规则会跳过；厂商文件里重名的中断只保留第一个并写警告（THA6412 的 `CPU3_PPI` 前 6 个名字误写成 `CPU0_` 开头）。内置的三颗芯片的外设段（含中断源）已按此方式从 ECU 资源生成，测试会检查两者保持一致。
- 单元格值按输入推断类型（`0x0C` → 12、`true` → 布尔），逗号分隔即列表；未改动的单元格保留原值。
- `resource_id` 为空或重复时不能保存。

### 硬件映射向导

- 打开项目时，向导的芯片来自项目：项目 `chips/` 里的副本优先，其次芯片库；默认选中项目的芯片。
- "Load from File…" 读取芯片 YAML 时会带上引脚表。

## 修复已有芯片

`ecu_resources` 是芯片数据的唯一权威，`resources`、`metadata.cores`、`ports` 都是由它推导出的视图。修复已有芯片时，先改 ECU 资源，再用它同步视图。修复不改芯片名，要改名请在设计器里另存为新芯片。缺失或待确认的数据只标记、不删除。

### 流程（`core/hardware/chip_repair.py`）

1. **取来源**：
   - `ecu_resources_from_properties(paths)`：读取一个或多个 `.properties`，后读的文件覆盖先读的同名键，不改动任何芯片；
   - `missing_key_changes(chip, keys)`：模块引用了、芯片却没有的键，作为值为空的新增项。
2. **看差异**：`diff_from_source(chip.ecu_resources, source)` 只比较来源里出现的模块，所以只含 Port 的文件不会把其他模块的键报成"删除"。
   - 按扁平键分为新增、删除、值变化三类。
   - 区间写法与列表写法算相同；只是类型不同（`1` 与 `"1"`）也算变化，并标出"仅类型不同"。
3. **选择性合并**：`apply_changes(chip, diff, keys)` 只应用选中的键，删除必须显式选中。已有键保持原位，新增键追加在所在模块末尾。
4. **同步视图**：`derive_views(chip)`。
   - 能推导的外设类型整类替换，推导不出的类型保留。
   - 核字段只在没有任何对应键与之相符时才改：THA610X 的 `Resource.NumOfCores` 是 2（含锁步核），`OsResource.NumOfCores` 是 1，现有值 2 保持不变。
   - 引脚表由 `ports_from_ecu` 推导，ECU 资源里没有 Port 数据时记为"未推导"。
5. **待确认标记**：`confirm_fields` 去掉标记，`mark_unconfirmed` 增加标记；两者都不改动被标记的数据。
6. **保存**：`save_repaired_chip(database, chip, base, record)`。
   - 改名、或文件在加载后被改过时拒绝保存。
   - 旧文件备份为 `<name>.yaml.bak`。
   - `resource_version` 默认末位加一，重新计算校验和，并刷新芯片库里的芯片。
   - 已经使用这颗芯片的项目，打开时会提示"芯片库有不同版本"。

### 修复向导

界面上用"芯片修复向导"（`ui/wizards/chip_repair_wizard.py`），三个入口：

- 主窗口 Tools › 修复芯片...
- 芯片定义设计器的"🔧 修复此芯片…"
- 项目属性里"资料不完整"旁边的"修复…"

六页依次是：选择芯片 → 修复来源 → 差异与选择 → 待确认标记 → 视图与检查 → 保存。各页之间的状态保存在 `RepairSession`（核心层，不依赖 Qt）里，命令行也用它合并来源。向导只修改芯片库；项目在 `chips/` 里有这颗芯片的副本时，会提示用"从芯片库更新"同步。

### 命令行

```bash
# 只看差异，不写文件
python -m tools.chip_repair diff THA6412_BGA516 new/CotexR52_THA6412_BGA516.properties
# 检查插件模块引用、芯片却没有的键
python -m tools.chip_repair diff THA6412_BGA516 --scan-dir test_import_project/Def/plugins
# 应用新增和变化（不含删除），同步视图，确认一个待确认项，保存
python -m tools.chip_repair apply THA610X_LFBGA180 new.properties --all-added --all-changed \
    --source "MCAL R440 CotexR52_THA610X_LFBGA180.properties" --note "补 Port 键" \
    --confirm "metadata.flash_size=按 SDK 链接脚本核对"
```

- `--keys K1,K2` 只应用列出的键；`--include-removed` 才会应用删除；`--version` 指定新版本号；`--chips-dir` 指定其他芯片库目录。
- 退出码：0 表示完成，1 表示参数错误或文件已被改动，2 表示没有可改的内容。

### 修改记录（`data/chips/history/<name>.yaml`）

每次保存追加一条，已有条目不改。修改记录不参与芯片校验和；芯片库只扫描 `data/chips/*.yaml`，不会把它当作芯片加载。

```yaml
chip: THA610X_LFBGA180
entries:
- date: '2026-10-28'
  author: <git config user.name，取不到时为操作系统用户名>
  source: MCAL R440 CotexR52_THA610X_LFBGA180.properties
  note: 补 Port 键
  resource_version: {old: 1.0.0, new: 1.0.1}
  base_modified_outside: false      # 修复前文件是否在设计器之外被改过
  ecu_resources:
    added:   [{key: Port.X, new: 3}]
    changed: [{key: Port.MaxAvailablePinID, old: 15, new: 16}]
    removed: []
  views: {resources: unchanged, metadata.cores: unchanged, ports: 'not derived: …'}
  confirmed: [{field: metadata.flash_size, note: 按 SDK 链接脚本核对}]
  marked: []
  checksum: sha256:…
```

芯片设计器自己的保存不写修改记录；需要留下记录的修改，请用修复向导或命令行。

## 已知限制

- Os 模板只定义了 `OS_CORE_ID_0/1`，4 核芯片的 `OS_CORE_ID_2/3` 在模板里是未定义的（模板问题，不在本功能内）。
- 不能从引脚表反向生成 `Port.*` 的模式列表（`InputModes*`、`OutputModes*` 等），引脚表只由 ECU 资源推导。
- 硬件映射向导的 Intc 页默认勾选全部中断源，THA6412 按默认设置会生成 942 个 `IntcSource_*` 容器；只配置用到的中断时请先取消勾选。
- 内置芯片的 Os 资源：THA6206、THA6412 已导入各自的 `Os_Resource_*.properties`（`tests/fixtures/ecu_resources/`）；THA610X 没有厂商 Os 资源文件，`OsResource.*`、`Os.*` 键缺失，Os 模块需要项目自带的 .properties。THA6206 的 `Os.IsrTriggerMethodList` 与 THA6412 逐项相同，导入时未改动，待厂商确认。
- 定义里的选择器取值范围在**解析定义时**确定：切换芯片或新增芯片后，已加载的模块要重新加载才会看到新的可选值。


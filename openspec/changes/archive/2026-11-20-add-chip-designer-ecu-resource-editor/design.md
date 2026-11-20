## Context

- `ChipDefinition.ecu_resources` 是 `{module: {name: value}}`，值为标量或标量列表；加载器 `parse_ecu_resources` 负责校验，区间写法由 `expand_ranges` / `compress_ranges` / `should_compress` 处理（`core/hardware/ecu_resource_data.py`）。
- 设计器把 ECU 资源暂存在 `self._ecu_resources`，保存时由 `_build_current_chip` 原样带入；目前只有导入按钮和只读预览（`ecu_preview`）。
- 诊断模块已有字面量引用的扫描（`_ECU_REF`、`collect_referenced_keys`）和一致性规则表（`CONSISTENCY_RULES`），目前只按"项目已加载的模块"收集。

## Goals / Non-Goals

- Goals：任何模块的任何键都能在界面里新建、修改、删除；长列表可编辑；厂商能看到还缺哪些键；不改数据格式。
- Non-Goals：不为具体外设做专用页面；不从引脚表推导 `Port.*`；不修改 `intc_sources`、各控制器差异化设置（见 proposal）。

## Decisions

### D1 编辑器直接操作 `self._ecu_resources`，不另存一份

用一个 `QStandardItemModel`（模块 → 键两级）展示；每次编辑立即写回 `self._ecu_resources`。写入前过 `normalize_value` 校验，与加载器同一套规则，所以界面能保存的内容一定能被重新加载。校验失败只提示并还原，不写入。

备选（不采用）：先编辑一份草稿、点"应用"再写回。多一层状态，且与现有"导入立即生效"的行为不一致。

### D2 值按形态编辑

| 值 | 编辑方式 |
|---|---|
| 标量（数字、布尔、字符串） | 单行输入；类型按输入内容推断，规则与 `.properties` 解析一致（整数、十六进制、浮点、`true/false`，其余为字符串） |
| 列表 | 逐项表格，可增删、上移下移 |
| 长列表（≥16 项且区间条目更少） | 区间表：两列"下标区间 / 值"，编辑后展开成完整列表再校验 |
| 含空格的长字符串（如 Port 的 `OutputModesXDMxx`） | 多行文本，原样保存，保留首个前导空格（见 `add-chip-yaml-ecu-resources` 的导出规则） |

区间表是同一份数据的另一种视图：切换视图不改变值。保存时是否用区间写法仍由 `should_compress` 决定，不由视图决定，保证输出确定。

### D3 所需键引导

1. 来源：用户选择一个插件根目录（可多个），或设计器由项目打开时取项目已加载模块的插件目录。
2. 扫描：对每个插件目录下的 `config/*.xdm`、`generate_PB/`、`generate_PC/` 用现有的 `_ECU_REF` 收集字面量键。把现有的"按项目收集"改成"按目录列表收集"的公共函数，项目版调用它，不复制逻辑。
3. 比对：被引用而当前芯片没有的键 → 列表，标注引用的模块；用户选中后"加入待填写"。
4. 待填写条目的值为 `None`（导出为 `Key:`），在树里高亮；保存时若仍有待填写条目，提示数量，用户可以选择继续保存。
5. 局限：只扫描字面量；被 `[!IF]` 保护、字符串拼接的键无法静态判断，列表上方固定注明。仅在其他芯片有值的键（如 THA610X 专用的 `Port.Available*`）不在本芯片的缺失列表里重复推荐，沿用诊断里的 `chip_specific` 规则。

### D4 一致性提示只提示

复用 `check_consistency`，结果显示在编辑页底部和预览页；不阻止保存，与诊断一致。

### D5 旧推导只加标注

`to_properties_string` 的旧分支（芯片无 `ecu_resources`）输出不变，只在设计器预览顶部加一行说明；`Adc.MaxResolution` 改取芯片的 ADC 分辨率。其余旧推导的已知问题（端口 ID、Cluster）不改值，写在 proposal 的非范围里，避免在没有数据模型的情况下"修成另一种错"。

### D6 标签页顺序

新页插入为第 4 页，预览页改为第 5 页。`_on_tab_changed` 里的页索引与 `tests/core/test_chip_designer.py` 里的 `setCurrentIndex(3)` 同步修改。

## Risks / Trade-offs

- **大数据量的界面性能。** 约 2450 个键、最长 1225 项的列表。树按模块折叠，键节点按需创建值编辑器，列表用表格视图而不是逐项控件。
- **类型推断与 properties 不一致。** 手输 `007` 会被推断成整数 7。缓解：提供"按字符串保存"的选项，并在输入框旁显示推断出的类型。
- **扫描误报。** 条件分支里的键会被当成"缺失"。缓解：见 D3 第 5 点，且只在用户主动点"扫描"时才运行。
- **与项目副本的关系。** 设计器保存到芯片库；项目内的副本不会随之变化（见 `add-chip-yaml-ecu-resources` 的 D8），要用"Update from Library"同步。

## Migration Plan

1. 先抽出按目录收集所需键的公共函数，不改现有行为。
2. 再做编辑器的模型与值编辑，最后做区间视图与引导。
3. 回滚：移除新标签页，数据格式没有变化，不需要迁移。

## Open Questions

1. 设计器能否直接打开项目内的 `chips/<芯片名>.yaml` 并保存回去（目前只操作芯片库）？这会让厂商能在项目里直接改数据，但需要另行设计入口，暂不纳入。
2. 键名是否提供自动补全（来自所需键列表和同模块已有键）？先不做，看使用反馈。

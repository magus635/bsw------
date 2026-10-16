## Why

芯片定义设计器只有 CAN、ADC、SPI 三页带类型的外设字段，而芯片的资源远不止这些。以 THA6412 的厂商文件为例，`CotexR52_THA6412_BGA516.properties` 约 2450 个键，分布在 Port、Gtm、Intc、Mcu、Adc、Dsadc、Iom、Dma、Can、Dio、Fls、Spi、Wdg、Resource 等近 20 个模块；`Os_Resource_THA6412.properties` 另有 `OsResource.*`、`Os.*`。这些数据现在都存放在芯片 YAML 的 `ecu_resources` 里（见 `add-chip-yaml-ecu-resources`），但设计器对它只提供"导入 .properties"和"只读预览"：

1. **不能新建、改值、删键。** 厂商要定制的内容（ISR 触发方式、Mcu 内存地址、Gtm/Intc 通道映射……）恰恰集中在这里，只能手改 YAML，或改 properties 后重新导入。
2. **不知道该填什么。** 界面没有任何入口告诉厂商：已加载的模块引用了哪些键、当前芯片还缺哪些。缺键只会在生成时静默得到空值。
3. **旧的推导会误导。** 没有 `ecu_resources` 的芯片导出时，旧逻辑会写出看似合理但错误的值（如 `Adc.MaxResolution` 固定为 12，不取界面上选的分辨率），预览里也没有标明这些是兜底值。

为每个外设单独做一页不可行：各模块键结构差异很大（Gtm 近 500 个按通道编号的键，Intc 有多级子键，Port 有上千个含空格的字符串），新外设就要改代码。因此做一个**通用的 ECU 资源编辑器**，再用"所需键"引导补全。

## What Changes

- **新增"ECU 资源"标签页**（放在"外设规格"与"预览与导出"之间）：左边按模块分组的树，右边编辑选中的键。
  - 可新增 / 删除模块、新增 / 删除 / 重命名键，修改值。
  - 值按形态编辑：标量（单行）、列表（逐项编辑，可增删排序）、长字符串（多行）。
  - 键名和值的限制与加载器完全一致（模块名不含 `.`；值为标量或标量列表），不合法时给出明确提示，不写入。
- **搜索与过滤**：按键名、值内容过滤；"仅看待填写"、"仅看有问题"。
- **区间列表编辑器**：长列表（如 992 项的 `Os.IsrTriggerMethodList`）以"下标区间 → 值"显示和编辑，保存时沿用现有的压缩与展开规则。
- **所需键引导**：扫描所选插件目录（或从项目打开设计器时，项目已加载模块）的 xdm 与模板，列出被 `ecu:get/ecu:list` 以字面量引用、而当前芯片尚无值的键，可一键加入"待填写"条目。结果会注明字面量扫描的局限。
- **一致性提示**：编辑器与预览页显示 `check_consistency` 的结果（个数与列表长度、主核写法等）；只提示，不阻止保存。
- **旧推导加标注**：芯片没有 `ecu_resources` 时，properties 预览顶部标明"兜底推导，非权威数据"；`Adc.MaxResolution` 改取界面上的分辨率。
- **标签页顺序**：原"4. 预览与导出"顺延为第 5 页，相关代码与测试里的页索引随之更新。

## Impact

- Affected specs: `chip-designer-ecu-editor`（新增能力）；依赖 `chip-ecu-resources`（`add-chip-yaml-ecu-resources`，已实现，待归档）。
- Affected code:
  - `autosar_configurator/ui/dialogs/chip_definition_designer_dialog.py`（新增标签页，页索引调整）
  - `autosar_configurator/ui/dialogs/` 下新增 ECU 资源编辑器部件（模型、树、值编辑器、区间编辑器）
  - `autosar_configurator/core/hardware/ecu_resource_data.py`（区间的取出 / 合并辅助函数，复用现有压缩与展开）
  - `autosar_configurator/core/hardware/ecu_resource_diagnostics.py`（按目录收集所需键；现有按项目收集的逻辑复用同一实现）
  - `autosar_configurator/core/hardware/chip_exporter.py`（旧推导的 `Adc.MaxResolution`）
  - 测试：`tests/ui/`、`tests/core/test_chip_designer.py`（页索引）
- 兼容性：不改变 YAML 格式、不改变 `ecu_resources` 的语义；不使用该页的用户行为与现在相同。
- **不在本变更范围内**（已知缺口，另行处理）：
  - 载入再保存时，多个 CAN/ADC/SPI 各自的差异化设置被全局设置覆盖；`intc_sources` 只能原样带过。
  - 从引脚表推导 `Port.*` 的模式列表（`InputModes*`、`OutputModes*`、`RXMUX_*`、`MUL_*`）：缺少权威映射规则，生成结果不可信。
  - 旧推导里的 `Port.MaxAvailablePortID`（取了端口个数而非最大端口号）与簇（Cluster）写死：需要端口编号与簇的数据模型，本变更只加标注，不改值。
  - 为单个外设做专用页面。
- 验证限制：所需键引导只能扫描字面量引用；字符串拼接构造的键、被条件分支保护的键无法静态判断，界面上注明。

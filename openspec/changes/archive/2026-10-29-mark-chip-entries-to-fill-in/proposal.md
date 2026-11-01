## Why

修复向导第 2 步"扫描所需但芯片没有的键"会把缺失键做成值为空（`null`，界面显示"（待填写）"）的新增项。这些项**默认勾选**，保存页也不像设计器那样提醒空值，一路"下一步"就会把 `null` 写进芯片 YAML。写进去之后问题就看不见了：

- 再次扫描（`missing_key_changes`）只看键在不在，不再报告；
- 工程诊断（`diagnose`）同样只看键在不在，不再告警"has no value"；
- 完整性检查（`check_chip`）不检查空值，芯片不会显示"（资料不完整）"。

模板里 `ecu:get()` 读到的却是空值。

不能简单地把所有 `null` 都当作待填写：芯片库里已有 49 个 `null`，全部来自厂商 `.properties` 的空值（例如 `CotexR52_THA6206_LFBGA292.properties` 的 `Gtm.TriggerXModule4:`），是合法数据；其中 `Port.DefaultHighStrengthCtrIPin`、`Port.AvailableLVDSPorts` 还被真实插件引用。

## What Changes

- 扫描得到的待填写项在修复向导里**不再默认勾选**；保存时如果本次新增了待填写项，先说明数量并询问是否保存。
- 待填写项写入芯片时，在 `metadata.unconfirmed` 加标记 `ecu_resources.<模块>.<键>: 待填写`。标记在**产生占位值的地方**加：修复会话（向导、命令行）里来自键扫描的新增项，以及设计器"4. ECU 资源"页"加入待填写"的条目。厂商文件中的空值不加标记。
- 条目有了值（设计器填写，或之后的修复从 `.properties` 得到值）或被删除时，自动去掉 `待填写` 标记，修复历史里记为已确认（说明"已填写"或"条目已删除"）。其他说明的标记不会被自动去掉。
- 打开工程时，所用芯片还有 `待填写` 标记的条目，在 ECU 资源诊断中逐个告警。
- 完整性检查不用改：`metadata.unconfirmed` 里的标记本来就会让芯片显示"（资料不完整）"，修复向导的第 1 步和第 5 步也会列出这些标记。

## Impact

- Affected specs：`chip-repair`（修改 `Change Selection In The Wizard`、`Saving From The Wizard`；新增 `Entries To Fill In Are Marked`）。
- `chip-ecu-resources`（尚未归档，见 `add-chip-yaml-ecu-resources`）的 `Missing And Inconsistent Key Diagnostics` 不变：本变更的告警通过芯片数据检查（`chip_data_findings`）给出，诊断对空值的处理保持原样。
- Affected code：`core/hardware/chip_repair.py`、`core/workspace_manager.py`、`ui/wizards/chip_repair_wizard.py`、`ui/dialogs/chip_definition_designer_dialog.py`、`ui/dialogs/ecu_resource_editor.py`。
- 兼容性：芯片库现有数据不变（49 个 `null` 都是厂商空值，不加标记）。现有测试都没有依赖"扫描键默认勾选"，不需要改动。
- **不在本变更范围内**：
  - 命令行 `--all-added` 仍然包含待填写项（参数是显式的），但保存时同样会加标记；
  - 设计器保存时的空值提醒（`count_placeholders`）仍按全部 `null` 计数，因此 THA6206、THA6412 每次保存都会提示二十多个"待填写"，其实全是厂商空值。这个误报应另开变更修复；
  - 设计器里手工"新增条目"或清空某个值产生的 `null` 不加标记（无法判断用户的意图）。
